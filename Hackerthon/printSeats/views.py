from django.shortcuts import render
from django.http import HttpResponse

# Create your views here.

def main(request):
    test = {'num1':1, 'num2':1}
    return render(request, 'index.html', test)

def introduce(request):
    return render(request, 'introduce.html')

def policy(request):
    return render(request, 'policy.html')

def service(request):
    return render(request, 'service.html')