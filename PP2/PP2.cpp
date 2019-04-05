#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include "SynchronizationPrimitiveKind.h"

int const DEFAULT_BANK_CLIENT_AMOUNT = 2;
std::string const EXIT_COMMAND = "exit";
std::string const QUIT_COMMAND = "quit";
std::string const CRITICAL_SECTION_KIND_STR = "criticalsection";
std::string const MUTEX_KIND_STR = "mutex";
std::string const NONE_KIND_STR = "none";
std::string const SHOW_HELP_COMMAND = "/?";

int GetBankClientsAmount(std::string numberStr);
void ShowTotalProgramStatistics(CBank* bank);
SynchronizationPrimitiveKind GetPrimitiveKindFromStr(std::string primmitiveKindStr);
void DoCommand(std::string command);
void ShowHelp();

int main(int argc, char* argv[])
{
	int bankClientsAmount = argc > 1 ? GetBankClientsAmount(argv[1]) : DEFAULT_BANK_CLIENT_AMOUNT;
	SynchronizationPrimitiveKind primitiveKind = argc > 2 ? GetPrimitiveKindFromStr(argv[2]) : SynchronizationPrimitiveKind::None;
	if (argc > 3)
	{
		DoCommand(argv[3]);
	}
	CBank* bank = new CBank(primitiveKind);

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
		if (command == EXIT_COMMAND || command == QUIT_COMMAND)
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
		int banckClientsAmount = 0;
		if (numberStr == "-")
		{
			std::cout << "Using bank client amount default value 2" << std::endl;
			return DEFAULT_BANK_CLIENT_AMOUNT;
		}
		banckClientsAmount = std::stoi(numberStr);
		if (banckClientsAmount > 0)
		{
			return banckClientsAmount;
		}
		else
		{
			std::cout << "Amount of bank client smaller 0, using bank client amount default value 2" << std::endl;
			return DEFAULT_BANK_CLIENT_AMOUNT;
		}
	}
	catch (std::exception ex)
	{
		std::cout << "Invalid type of  bank client amount, using bank client amount default value 2" << std::endl;
		return DEFAULT_BANK_CLIENT_AMOUNT;
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

SynchronizationPrimitiveKind GetPrimitiveKindFromStr(std::string primmitiveKindStr)
{
	std::transform(primmitiveKindStr.begin(), primmitiveKindStr.end(), primmitiveKindStr.begin(), ::tolower);
	if (primmitiveKindStr == CRITICAL_SECTION_KIND_STR)
	{
		return SynchronizationPrimitiveKind::CriticalSection;
	}
	if (primmitiveKindStr == MUTEX_KIND_STR)
	{
		return SynchronizationPrimitiveKind::Mutex;
	}
	if (primmitiveKindStr == "-")
	{
		std::cout << "None kind was choosen as default" << std::endl;
		return SynchronizationPrimitiveKind::None;
	}
	if (primmitiveKindStr != NONE_KIND_STR)
	{
		std::cout << "Unknown primitive kind. None kind was choosen as default";
	}
	return SynchronizationPrimitiveKind::None;
}

void DoCommand(std::string command)
{
	if (command == "-")
	{
		return;
	}
	if (command == SHOW_HELP_COMMAND)
	{
		ShowHelp();
		return;
	}
	std::cout << "Unknown command" << std::endl;
}

void ShowHelp()
{
	std::cout << "Template: PP2.exe <amount of bank clients> <synchronization primitive kind> <command>" << std::endl;
	std::cout << "  <amount of bank client>:" << std::endl
		<< "    type: int, only bigger 0" << std::endl 
		<< "    default value: 2" << std::endl;
	std::cout << "  <synchronization primitive kind>:" << std::endl
		<< "    mutex: for using mutex" << std::endl
		<< "    criticalSection: for using criticalSection" << std::endl
		<< "    none: for working without synchronization primitive" << std::endl
		<< "    default value: None" << std::endl;
	std::cout << "  <command>:" << std::endl
		<< "    any available command" << std::endl;
	std::cout << "For using default value enter - in place of required value" << std::endl;
	std::cout << "In case of incorrect work will be used default value" << std::endl;
	std::cin.get();
}