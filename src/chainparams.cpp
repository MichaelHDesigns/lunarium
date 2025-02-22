// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin developers
// Copyright (c) 2014-2019 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2017-2019 The Phore developers
// Copyright (c) 2018-2019 The Lunarium developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (      0, uint256("0000086041e4ff304ec6349b4270dc53a354b5a44f3216278aae188fe862ad35"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
	1644193942, // * UNIX timestamp of last checkpoint block
	0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    0        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1644193942,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1644193942,
    0,
    0};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus;
    bnTrustedModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

libzerocoin::ZerocoinParams* CChainParams::OldZerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus;
    bnTrustedModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa9;
        pchMessageStart[1] = 0xc6;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0xea;
        nDefaultPort = 61050;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 30; // Lunarium: 1 day
        nTargetSpacing = 30;  // Lunarium: 1 minute
        nMaturity = 6;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 100000000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 100;
        nZerocoinStartHeight = 100; // Chain moving at normal pace at this block.

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Devilking6105 says love life and inspire others";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 5000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("047eac5e017985914ae18805ce5f3b29b79647db903a99c0244295a83081c567b3ea82238ab1e8bbc26c91578321bd1136cc4385df4572b703d16623d50a3a819e") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1644193942;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 22225380;

        // Uncomment the following block of code if you want to create a genesis block by running ./lunariumd.
        // Make sure to create a new psztimestamp and set your nonce to 0 before compiling, also comment out the assert lines below this block!
        /*printf("calc new genesis block\n");
        printf("hashMerkleRoot %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("bnProofOfWorkLimit 0x%x\n", bnProofOfWorkLimit.GetCompact());
        printf("genesis.nBits 0x%x\n", genesis.nBits);

        for (genesis.nNonce = 0; ; genesis.nNonce++) {
          hashGenesisBlock = genesis.GetHash();
          if (hashGenesisBlock <= bnProofOfWorkLimit) break;
        }

        printf("hashGenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
        printf("genesis.nNonce %d\n", genesis.nNonce);
        printf("genesis.nTime %d\n", genesis.nTime);*/

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000086041e4ff304ec6349b4270dc53a354b5a44f3216278aae188fe862ad35"));
        assert(genesis.hashMerkleRoot == uint256("0xa233372d6684ae95332b618af7a8df6a8cd5e10391ed4ab8d22f738920916727"));

     //   vSeeds.push_back(CDNSSeedData("vps01", "seed1.explorerxln.com"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 26);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x02)(0x86).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "brs";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "048aa0e5c422632834bffd0588817bf90d7b19423a9d6b6959bc480d0d8bfc837ef6d4d6f90213bcde3e8a160dc7fa98840555e0bf0d7402001eafdcb8e6a5a18d";
        strObfuscationPoolDummyAddress = "LCYiHgGJJ6xGHqivmdZrYjRnhaYf6AJ2Mp";

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";

        nZerocoinLastOldParams = 99999999; // Updated to defer zerocoin v2 for further testing.
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudgetFeeConfirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x47;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        nDefaultPort = 45071;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Lunarium: 1 day
        nTargetSpacing = 1 * 10;  // Lunarium: 1 minute
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nMaxMoneyOut = 43199500 * COIN;
        nLastPOWBlock = 3000;
        nZerocoinStartHeight = 200;

        nZerocoinLastOldParams = 100000000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1644193942;
        genesis.nNonce = 22225380;

        // Uncomment for genesis block creation
        /*printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        {
          printf("(test)calc new genesis block\n");
          printf("hashMerkleRoot %s\n", genesis.hashMerkleRoot.ToString().c_str());
          printf("bnProofOfWorkLimit 0x%x\n", bnProofOfWorkLimit.GetCompact());
          printf("genesis.nBits 0x%x\n", genesis.nBits);

          for (genesis.nNonce = 0; ; genesis.nNonce++) {
            hashGenesisBlock = genesis.GetHash();
            if (hashGenesisBlock <= bnProofOfWorkLimit) break;
          }

          printf("hashGenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
          printf("genesis.nNonce %d\n", genesis.nNonce);
        }*/

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000086041e4ff304ec6349b4270dc53a354b5a44f3216278aae188fe862ad35"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 80); // Testnet lunarium addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 81);  // Testnet lunarium script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet lunarium BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet lunarium BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet lunarium BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "tbrs";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        // Priv key: 93HghXW2rpbfPSjTzbncv5EAdhRMhjKXPcxsqDVQXd5nEk3aWnp
        strSporkKey = "04396ada3ef4564da3121847866853a9c8dd20eed1f2b72d36b54a081bd49e6e724d0bb6100aa957e1846e931a5cb09fd9dacca7a4286694733b366d2770609ea3";
        strObfuscationPoolDummyAddress = "y3csZHtDJf9Q5AzshojX39h3wvJNcRUEWA";
        nBudgetFeeConfirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                     // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Lunarium: 1 day
        nTargetSpacing = 1 * 60;        // Lunarium: 1 minutes
        bnProofOfWorkLimit = 0x207fffff; //~uint256(0) >> 1;
        genesis.nTime = 1644193942;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 22225380;
        nMaturity = 0;
        nLastPOWBlock = 999999999; // PoS complicates Regtest because of timing issues
        nZerocoinLastOldParams = 499;
        nZerocoinStartHeight = 100;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 45071;

        // Uncomment for genesis block creation
        /*printf("hashGenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
        printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());

        {
          printf("(regtest)calc new genesis block\n");
          printf("hashMerkleRoot %s\n", genesis.hashMerkleRoot.ToString().c_str());
          printf("bnProofOfWorkLimit 0x%x\n", bnProofOfWorkLimit.GetCompact());
          printf("genesis.nBits 0x%x\n", genesis.nBits);

          for (genesis.nNonce = 0; ; genesis.nNonce++) {
            hashGenesisBlock = genesis.GetHash();
            if (hashGenesisBlock <= bnProofOfWorkLimit) break;
          }

          printf("hashGenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
          printf("genesis.nNonce %d\n", genesis.nNonce);
        }*/

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000086041e4ff304ec6349b4270dc53a354b5a44f3216278aae188fe862ad35"));
        //assert(hashGenesisBlock == uint256("0x1a7470545e23b0d3aa579386d55278488a34a98352d1f785c1706b760bbf0688"));

        bech32_hrp = "brsrt";

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        nRequiredAccumulation = 1;

        strSporkKey = "048aa0e5c422632834bffd0588817bf90d7b19423a9d6b6959bc480d0d8bfc837ef6d4d6f90213bcde3e8a160dc7fa98840555e0bf0d7402001eafdcb8e6a5a18d";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 45072;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
