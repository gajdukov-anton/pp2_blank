#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <mutex>

#include "BankClient.h"
#include "SynchronizationPrimitiveKind.h"

class CBank
{
public:
	CBank(SynchronizationPrimitiveKind primitiveKind);
	~CBank();
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
	CRITICAL_SECTION m_critsect;
	std::mutex m_updateClientBalanceMutex;
	SynchronizationPrimitiveKind m_primitiveKind;

	void SetTotalBalance(int value);
	void SomeLongOperations();
};