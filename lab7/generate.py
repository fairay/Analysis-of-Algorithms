from faker import Faker
rec_n = 1500
fname = 'data.txt'

if __name__ == "__main__":
    fake = Faker("ru_Ru")
    f = open(fname, 'w')
    
    c = 0
    key = '9'
    for i in range(rec_n):
        card_n = fake.credit_card_number()
        cvc = fake.credit_card_security_code()
        
        while (len(str(card_n)) != 16):
            card_n = fake.credit_card_number()
        while (len(str(cvc)) != 3):
            cvc = fake.credit_card_security_code()
        print(card_n, cvc,
              sep="\t", end="\n", file=f)
        
        if (str(card_n)[:1] == key):
            c+=1
    f.close()

    print(key, c)
