import numpy as np
import ctypes

dll = ctypes.CDLL("libalgo_c.so")

dll.radix_argsort_u16.argtypes = [ctypes.POINTER(ctypes.c_uint16), ctypes.POINTER(ctypes.c_uint16), ctypes.c_int64]
dll.bucket_argsort_u16.argtypes = [ctypes.POINTER(ctypes.c_uint16), ctypes.POINTER(ctypes.c_uint16), ctypes.c_int64]
dll.quick_argsort_u16.argtypes = [ctypes.POINTER(ctypes.c_uint16), ctypes.POINTER(ctypes.c_uint16), ctypes.c_int64]


def radix_argsort(array: np.array):
    if not array.dtype is np.dtype(np.uint16):
        raise NotImplementedError("radix_argsort does not support type %s" % array.dtype.name)
    result = np.zeros(len(array))
    dll.radix_argsort_u16(array.ctypes.data_as(ctypes.POINTER(ctypes.c_uint16)), result.ctypes.data_as(ctypes.POINTER(ctypes.c_uint16)), len(array))
    return result


def bucket_argsort(array: np.array):
    if not array.dtype is np.dtype(np.uint16):
        raise NotImplementedError("bucket_argsort does not support type %s" % array.dtype.name)
    result = np.zeros(len(array))
    dll.bucket_argsort_u16(array.ctypes.data_as(ctypes.POINTER(ctypes.c_uint16)), result.ctypes.data_as(ctypes.POINTER(ctypes.c_uint16)), len(array))
    return result


def quick_argsort(array: np.array):
    if not array.dtype is np.dtype(np.uint16):
        raise NotImplementedError("quick_argsort does not support type %s" % array.dtype.name)
    result = np.zeros(len(array))
    dll.quick_argsort_u16(array.ctypes.data_as(ctypes.POINTER(ctypes.c_uint16)), result.ctypes.data_as(ctypes.POINTER(ctypes.c_uint16)), len(array))
    return result

