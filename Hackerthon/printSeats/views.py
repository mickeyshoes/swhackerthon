from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt

# Create your views here.

@csrf_exempt
def main(request):

    import serial

    arduino = serial.Serial('COM4', 9600, timeout = .1) 
    print(arduino)

    i = 0

    while True:
        datas = arduino.readline()
        if datas:
            print(i,": ",datas)
            i = i + 1
            break

    print(datas)
    datas = datas.decode('utf-8')
    print(type(datas))

    #공백 문자열인 경우 제거
    if datas:
        data_list = datas.split('/')
        print(data_list)
        send_data_list = {}

        for i in data_list:
            #공백 문자열인 경우 제거
            if i:
                temp = i.split(':')
                print(temp)
                send_data_list[temp[0]] = int(temp[1])

        print(send_data_list)

    elif datas ==['']:
        pass

    return render(request, 'index.html', send_data_list)

def introduce(request):
    return render(request, 'introduce.html')

def policy(request):
    return render(request, 'policy.html')

def service(request):
    return render(request, 'service.html')