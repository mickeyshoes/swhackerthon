from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
import asyncio

# Create your views here.

async def getAsyncDatas():
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


    return send_data_list

def getSeatInfo(request):
    send_data_list = asyncio.run(getAsyncDatas())
    import json
    data = json.dumps(send_data_list)
    return HttpResponse(data)

@csrf_exempt
def main(request):
    # send_data_list = asyncio.run(getAsyncDatas())
    send_data_list = {}
    # return render(request, 'index.html', send_data_list)
    return render(request, 'home_copy.html', send_data_list)

def introduce(request):
    return render(request, 'introduce.html')

def policy(request):
    return render(request, 'policy.html')

def service(request):
    return render(request, 'service.html')

def seat(request):
    return render(request, 'seat.html')