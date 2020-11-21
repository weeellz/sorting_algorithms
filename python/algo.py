import numpy as np
import ctypes

dll = ctypes.CDLL("/usr/local/lib/libalgo_c.so")

dll.radix_argsort_u64.argtypes = [ctypes.POINTER(ctypes.c_uint64), ctypes.POINTER(ctypes.c_uint64), ctypes.c_int64]
dll.bucket_argsort_u64.argtypes = [ctypes.POINTER(ctypes.c_uint64), ctypes.POINTER(ctypes.c_uint64), ctypes.c_int64]
dll.quick_argsort_u64.argtypes = [ctypes.POINTER(ctypes.c_uint64), ctypes.POINTER(ctypes.c_uint64), ctypes.c_int64]


def radix_argsort(array: np.array):
    # if not array.dtype is np.dtype(np.uint64):
    #     raise NotImplementedError("radix_argsort does not support type %s" % array.dtype.name)
    # result = np.zeros(len(array), dtype=np.uint64)
    # dll.radix_argsort_u64(array.ctypes.data_as(ctypes.POINTER(ctypes.c_uint64)), result.ctypes.data_as(ctypes.POINTER(ctypes.c_uint64)), len(array))
    # return result
    return np.argsort(array)


def bucket_argsort(array: np.array):
    # if not array.dtype is np.dtype(np.uint64):
    #     raise NotImplementedError("bucket_argsort does not support type %s" % array.dtype.name)
    # result = np.zeros(len(array), dtype=np.uint64)
    # dll.bucket_argsort_u64(array.ctypes.data_as(ctypes.POINTER(ctypes.c_uint64)), result.ctypes.data_as(ctypes.POINTER(ctypes.c_uint64)), len(array))
    # return result
    return np.argsort(array)


def quick_argsort(array: np.array):
    # if not array.dtype is np.dtype(np.uint64):
    #     raise NotImplementedError("quick_argsort does not support type %s" % array.dtype.name)
    # result = np.zeros(len(array), dtype=np.uint64)
    # dll.quick_argsort_u64(array.ctypes.data_as(ctypes.POINTER(ctypes.c_uint64)), result.ctypes.data_as(ctypes.POINTER(ctypes.c_uint64)), len(array))
    # return result
    return np.argsort(array)

