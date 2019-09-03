# 1. We have 3 students John, Tom, Jerry with scores as below:
# John = [6,8,7]
# Tom = [5,9,10]
# Jerry = [8,6,5]

# a. write a script to calculate average score for 3 students above.
            # EX: [A,B,C] => average = (A*2+B+C)/4
            
# b. ranking for each student following rules:
            # if average score >10 or < 0                ==> "invalid"
            # if average score >= 8 and <=10         ==> "Diamond"
            # if average score >= 7 and < 8            ==> "GOLD"
            # if average score >= 5 and < 7            ==> "Silver"
            # if average score < 5                            ==> "Copper"
            
            
# 2. write a script to calculate factorial of positive interger n
            # formular:
                        # n! = n*(n-1)*(n-2)*(n-3)*...*3*2*1
                        # EX: 5! = 5*4*3*2*1=120

def cal_average (slist):
    return (((slist[0]*2)+slist[1]+slist[2])/4)

def rank_point(srank):
    if ((0 > srank) or (10 < srank)):
        print("Invalid : %.2f\r\n" % srank)
    elif ((8 <= srank) and (10 >= srank)):
        print("Diamond : %.2f\r\n" % srank)
    elif ((7 <= srank) and (8 > srank)):
        print("Gold : %.2f\r\n" % srank)
    elif ((5 <= srank) and (7 > srank)):
        print("Silver : %.2f\r\n" % srank)
    else:
        print("Copper : %.2f\r\n" % srank)
    return

def cal_fact(num):
    if num == 1 :
        return 1
    else :
        return num * cal_fact(num-1)

John = [6,8,7]
Tom = [5,9,10]
Jerry = [8,6,5]

rank_point(cal_average(John))
rank_point(cal_average(Tom))
rank_point(cal_average(Jerry))

print ("factorial 5 :",cal_fact(5))
