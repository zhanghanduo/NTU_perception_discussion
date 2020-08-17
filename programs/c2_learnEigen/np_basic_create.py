import numpy as np
from icecream import ic

if __name__ == '__main__':
    array_1 = np.arange(20)
    # ic(array_1)
    # ic(array_1.shape)
    # ic(array_1[3])

    array_1[3] = 100

    array_2 = array_1.reshape(4, 5)
    # ic(array_2.shape)
    # ic(array_2[3][4])

    array_3 = np.arange(35, 10, -3)
    # ic(array_3)

    # np.empty((2, 4)) gives random values.
    a_1 = np.zeros((2, 4))
    # ic(a_1)

    # np.full((3, 4),3) filled with 3.
    # np.eye(3, 3) gives diagonal 1s others 0.
    a_2 = np.ones((3, 4))
    # ic(a_2)

    # linspace gives evenly spaced numbers over an interval.
    a_3 = np.linspace(0, 10, num=4)
    # ic(a_3)

    p_list = [4, 5, 6]
    a_4 = np.array(p_list)
    ic(type(a_4))

    a_5 = np.random.random((2, 2))
    a_6 = np.random.randint(5, size = (2, 2))
