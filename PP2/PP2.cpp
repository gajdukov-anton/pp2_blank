#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"

int const DEFAULT_BANK_CLIENT_AMOUNT = 2;
std::string const EXIT_COMMAND = "exit";
std::string const QUIT_COMMAND = "quit";

int GetBankClientsAmount(std::string numberStr);
void ShowTotalProgramStatistics(CBank* bank);

int main(int argc, char* argv[])
{
	CBank* bank = new CBank();
	int bankClientsAmount = argc > 1 ? GetBankClientsAmount(argv[1]) : DEFAULT_BANK_CLIENT_AMOUNT;

	for (int i = 0; i < bankClientsAmount; i++)
	{
		bank->CreateClient();
	}


	std::string command = "";
	// TODO: WaitForMultipleObjects
	while (command != EXIT_COMMAND && command != QUIT_COMMAND)
	{
		std::cin >> command;
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);
		if (command == EXIT_COMMAND)
		{
			ShowTotalProgramStatistics(bank);
		}
	}

    return 0;
}

int GetBankClientsAmount(std::string numberStr)
{
	try
	{
		return std::stoi(numberStr);
	}
	catch (std::exception ex)
	{
		std::cout << "Invalid type of  bank client amount" << std::endl;
		return 0;
	}
}

void ShowTotalProgramStatistics(CBank* bank)
{
	std::cout << "Bank total balance: " << bank->GetTotalBalance() << std::endl;
	std::cout << "Amount of balances of the customers: " << bank->GetTotalBalanceOfAllClients() << std::endl;
	std::cout << "Clients: " << std::endl;
	for each (CBankClient client in bank->GetClients())
	{
		std::cout << "  client " << client.GetId() << ": " << bank->GetClientBalanceMap()[client.GetId()] << std::endl;
	}
}
