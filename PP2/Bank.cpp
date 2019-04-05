#include "Bank.h"

CBank::CBank(SynchronizationPrimitiveKind primitiveKind)
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
	m_primitiveKind = primitiveKind;
	InitializeCriticalSection(&m_critsect);
}

CBank::~CBank()
{
	DeleteCriticalSection(&m_critsect);
}

CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	m_clientBalance.insert(std::pair<unsigned, int>(clientId, 0));
	return client;
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	if (m_primitiveKind == SynchronizationPrimitiveKind::CriticalSection)
		EnterCriticalSection(&m_critsect);
	else if (m_primitiveKind == SynchronizationPrimitiveKind::Mutex)
		m_updateClientBalanceMutex.lock();

	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	totalBalance += value;
	m_clientBalance[client.GetId()] += value;
	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance != GetTotalBalance() + value) {
		std::cout << "! ERROR !" << std::endl;
	}

	SetTotalBalance(totalBalance);

	if (m_primitiveKind == SynchronizationPrimitiveKind::CriticalSection)
		LeaveCriticalSection(&m_critsect);
	else if (m_primitiveKind == SynchronizationPrimitiveKind::Mutex)
		m_updateClientBalanceMutex.unlock();
}


int CBank::GetTotalBalance() const
{
	return m_totalBalance;
}

std::vector<CBankClient> CBank::GetClients() const
{
	return m_clients;
}

int CBank::GetTotalBalanceOfAllClients() const
{
	int totalBalance = 0;
	for (auto it = m_clientBalance.begin(); it != m_clientBalance.end(); ++it)
	{
		totalBalance += it->second;
	}
	return totalBalance;
}

std::map<unsigned, int> CBank::GetClientBalanceMap() const
{
	return m_clientBalance;
}

void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations()
{
	Sleep(1000);
}