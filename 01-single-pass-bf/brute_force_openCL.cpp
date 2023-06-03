#include <iostream>
#include <cmath>
#include <unistd.h>
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

#define ASCII_START 97 // a
#define ASCII_END 122  // z
#define PASS_LEN 8
#define THREADS 12
#define ALPHABET_SIZE (ASCII_END - ASCII_START + 1)

void bruteForce(std::string cipher, bool verbose, bool flsh) {
    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;

    fp = fopen("bf_kernel.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
                          &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    cl_mem memobjInput = NULL;
    cl_mem memobjOutput = NULL;
    memobjInput = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(char) * (PASS_LEN), NULL, &ret);
    memobjOutput = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(char) * (PASS_LEN), NULL, &ret);

    ret = clEnqueueWriteBuffer(command_queue, memobjInput, CL_TRUE, 0, sizeof(char) * (PASS_LEN), &cipher, 0,
                               NULL, NULL);

    if (ret != CL_SUCCESS) {
        printf("\n Error number %d", ret);
    }
}

int main() {
    std::string plain = "abcd";
    bool verbose = false;
    bool flsh = false;
    bruteForce(plain, verbose, flsh);
    return 0;
}