import pdb

def test():
    print('test...')

def main():
    print('Calling python script success...')

    #pdb.set_trace()
    a = 1 + 1
    print('a = 1+1 = %d' %a)

if __name__ == "__main__":
    main()
    print("calling __main__ success...")
