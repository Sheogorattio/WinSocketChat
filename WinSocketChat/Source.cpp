//Main.cpp
#include <iostream>
#include "Socket.h"

using namespace std;

int prices[3] = { 14000, 18000, 28000 };

int main()
{
	int nChoice;
	int port = 24242; //выбираем порт
	string ipAddress; //Адрес сервера
	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];
	cout << "1) Start server" << endl;
	cout << "2) Connect to server" << endl;
	cout << "3) Exit" << endl;
	cin >> nChoice;
	if (nChoice == 1)
	{
		ServerSocket server;
		cout << "Starting server..." << endl;
		//Запускаем сервер
		server.StartHosting(port);
		while (true)
		{
			int code, number;
			char rez[MAXSTRLEN]="total price is ";
			
			cout << "\tWaiting..." << endl;
			//Получаем данные от клиента
			//и сохраняем в переменной receiveMessage
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			code = atoi(receiveMessage);
			//Отправляем данные клиенту
			server.SendDataMessage("Enter number\n");
			cout << "\tWaiting..." << endl;
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			number = atoi(receiveMessage);
			
			char totPrice[MAXSTRLEN];
			_itoa_s(number * prices[code - 1], totPrice, 10);
			strcat_s(rez, MAXSTRLEN, totPrice);
			server.SendDataMessage(totPrice);
			cout << "\tWaiting..." << endl;
			//Если есть сообщение "end", завершаем работу
		/*	if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)*/
				break;
		}
	}
	else if (nChoice == 2)
	{
		cout << "Enter an IP address: " << endl;
		//Запрашиваем IP сервера
		cin >> ipAddress;
		ClientSocket client;
		//подключаемся к серверу
		client.ConnectToServer(ipAddress.c_str(), port);
		cout << "1) phone 14000\n2)tablet 18000\n3)laptop 28000\nEnter code(1/2/3)\n";
		while (true)
		{
			
			//отправляем сообщение
			char message[MAXSTRLEN];
			
			cin.ignore();
			cout << "Input message: ";
			cin.get(message, MAXSTRLEN);
			client.SendDataMessage(message);
			cout << "\tWaiting" << endl;
			//получаем ответ
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			if (
				strcmp(sendMessage, "end") == 0)
				break;
		}
		//Закрываем соединение
		client.CloseConnection();
	}
	else if (nChoice == 3)
		return 0;
}










