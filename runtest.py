import pdb
import numpy as np

def test():
    print('Test numpy module...')
    tArray = np.random.randn(2,3)
    print(tArray)

def main():
    print('Calling python script success...')

    #pdb.set_trace()
    a = 1 + 1
    print('a = 1+1 = %d' %a)

if __name__ == "__main__":
    main()
    print("calling __main__ success...")
