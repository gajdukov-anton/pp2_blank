#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "BankClient.h"

class CBank
{
public:
	CBank();
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	int GetTotalBalance() const;
	std::vector<CBankClient> GetClients() const;
	int GetTotalBalanceOfAllClients() const;
	std::map<unsigned, int> GetClientBalanceMap() const;

private:
	std::vector<CBankClient> m_clients;
	int m_totalBalance;
	std::map<unsigned, int> m_clientBalance;

	void SetTotalBalance(int value);
	void SomeLongOperations();
};