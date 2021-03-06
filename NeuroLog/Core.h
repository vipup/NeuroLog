// Copyright (c) CEZEO software Ltd. http://www.cezeo.com

#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Subnet.h"
#include "RawSubnet.h"
#include "SubnetHit.h"
#include "AppLog.h"

class Core
{
public:

	Core();
	~Core();

	bool LoadSubnets();
	bool LoadLogs();
	void AnalyzeSubnets();
	void ClearData();

	std::wstring subnetsFolder;
	std::wstring outputFolder;
	std::wstring logsFolder;
	std::wstring logsMask;

	uint32 sizeLimit; //  Do not include subnets into report when they generated less traffic that this value
	uint32 hitsLimit; //  Do not include subnets into report when they generated less hits that this value

	// Logging object
	AppLog appLog;

	// Array of subnets
	std::vector< Subnet > subnetsVector;

	// Array of Hits files
	std::vector< Hit > hitsVector;

	// Map of Request URIs
	std::unordered_map< std::string, uint32 > uriMap;

	// Map of Referrers
	std::unordered_map< std::string, uint32 > refMap;

	// Map of User Agents
	//std::unordered_map< std::string, uint32 > agentsMap;

	size_t totalHitsSession;

private:

	#pragma region Subnets

	bool LoadSubnetsCache( std::vector<RawSubnet>* pRawSubnets );
	bool BuildSubnets( std::vector<RawSubnet>* pRawSubnets );
	bool ParseSubnetsFile( std::vector<RawSubnet>* pRawSubnets, std::wstring subnetsFilePath );
	bool ParseSubnetsCsvFile( std::vector<RawSubnet>* pRawSubnets, std::wstring subnetsFilePath );

	#pragma endregion

	#pragma region System

	size_t GetFilesByMask( std::vector< std::wstring >* fileNames, std::wstring folder, std::wstring mask );
	std::string MakeBytesSizeString( uint64 value );
	std::string Ipv4ToString( uint32 ipv4 );
	byte SetCIDR( uint32 ips );
	#pragma endregion

	#pragma region Logs

	bool ParseLogFile( std::wstring fileName );

	#pragma endregion

	LPSUBNETHIT ipMap[65536]{}; // using two octets of IP address to find subnet block faster

};
typedef Core* LPCORE;

