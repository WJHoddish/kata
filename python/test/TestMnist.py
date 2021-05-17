import struct

import numpy as np

train_images_idx3_ubyte_file = './MNIST/train-images-idx3-ubyte'
train_labels_idx1_ubyte_file = './MNIST/train-labels-idx1-ubyte'

test_images_idx3_ubyte_file = './MNIST/t10k-images-idx3-ubyte'
test_labels_idx1_ubyte_file = './MNIST/t10k-labels-idx1-ubyte'


def decode_idx3_ubyte(idx3_ubyte_file):
    bin_data = open(idx3_ubyte_file, 'rb').read()  # binary data

    offset = 0
    fmt_header = '>IIII'
    magic_number, num_images, num_rows, num_cols = struct.unpack_from(fmt_header, bin_data, offset)
    print("magic: %d, count: %d, size: %d * %d" % (magic_number, num_images,  # train set
                                                   num_rows, num_cols))

    image_size = num_rows * num_cols
    offset += struct.calcsize(fmt_header)
    fmt_image = '>' + str(image_size) + 'B'
    images = np.empty((num_images, num_rows, num_cols))
    for i in range(num_images):
        if (i + 1) % 10000 == 0:
            print("done %d" % (i + 1), "pictures")
        images[i] = np.array(struct.unpack_from(fmt_image, bin_data, offset)).reshape((num_rows, num_cols))
        offset += struct.calcsize(fmt_image)

    return images


def decode_idx1_ubyte(idx1_ubyte_file):
    bin_data = open(idx1_ubyte_file, 'rb').read()

    offset = 0
    fmt_header = '>II'
    magic_number, num_images = struct.unpack_from(fmt_header, bin_data, offset)
    print("magic: %d, num_images: %d" % (magic_number, num_images))

    offset += struct.calcsize(fmt_header)
    fmt_image = '>B'
    labels = np.empty(num_images)
    for i in range(num_images):
        if (i + 1) % 10000 == 0:
            print("done %d" % (i + 1) + "zhang")
        labels[i] = struct.unpack_from(fmt_image, bin_data, offset)[0]
        offset += struct.calcsize(fmt_image)

    return labels  # ndarray


if __name__ == '__main__':
    train_images = decode_idx3_ubyte(train_images_idx3_ubyte_file)
    train_labels = decode_idx1_ubyte(train_labels_idx1_ubyte_file)
