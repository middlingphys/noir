// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_PARAMS_H
#define BITCOIN_CONSENSUS_PARAMS_H

#include "uint256.h"
#include <map>
#include <string>

namespace Consensus {

enum DeploymentPos
{
    DEPLOYMENT_TESTDUMMY,
    DEPLOYMENT_CSV, // Deployment of BIP68, BIP112, and BIP113.
    DEPLOYMENT_SEGWIT, // Deployment of BIP141, BIP143, and BIP147.
    // NOTE: Also add new deployments to VersionBitsDeploymentInfo in versionbits.cpp
    MAX_VERSION_BITS_DEPLOYMENTS
};

/**
 * Struct for each individual consensus rule change using BIP9.
 */
struct BIP9Deployment {
    /** Bit position to select the particular bit in nVersion. */
    int bit;
    /** Start MedianTime for version bits miner confirmation. Can be a date in the past */
    int64_t nStartTime;
    /** Timeout/expiry MedianTime for the deployment attempt. */
    int64_t nTimeout;
};

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;
    /** Used to check majorities for block version upgrade */
    int nMajorityEnforceBlockUpgrade;
    int nMajorityRejectBlockOutdated;
    int nMajorityWindow;
    /** Block height and hash at which BIP34 becomes active */
    int BIP34Height;
    uint256 BIP34Hash;
    /**
     * Minimum blocks including miner confirmation of the total of 2016 blocks in a retargetting period,
     * (nPowTargetTimespan / nPowTargetSpacing) which is also used for BIP9 deployments.
     * Examples: 1916 for 95%, 1512 for testchains.
     */
    uint32_t nRuleChangeActivationThreshold;
    uint32_t nMinerConfirmationWindow;
    BIP9Deployment vDeployments[MAX_VERSION_BITS_DEPLOYMENTS];
    /** Proof of work parameters */
    uint256 powLimit;
    uint256 posLimit;
    bool fPowAllowMinDifficultyBlocks;
    bool fPowNoRetargeting;
    int64_t nPowTargetSpacing;
    int64_t nPowTargetTimespan;
    int64_t nChainStartTime;
    unsigned char nMinNFactor;
    unsigned char nMaxNFactor;
    
    int nInstantSendKeepLock; // in blocks
    //int nBudgetPaymentsStartBlock;
    //int nBudgetPaymentsCycleBlocks;
    //int nBudgetPaymentsWindowBlocks;
    int nNoirnodeMinimumConfirmations;
    int nNoirnodePaymentsStartBlock;
    //int nNoirnodePaymentsIncreaseBlock;
    //int nNoirnodePaymentsIncreasePeriod; // in blocks
    //int nSuperblockStartBlock;

    //////////////////////////////////
    // Sigma   
    //////////////////////////////////

    // The block number after which sigma are accepted.
    int nSigmaStartBlock;

    int nSigmaPaddingBlock;

    int nDisableUnpaddedSigmaBlock;
    
    // Amount of maximum sigma spend per block.
    unsigned nMaxSigmaInputPerBlock;

    // Value of maximum sigma spend per block.
    int64_t nMaxValueSigmaSpendPerBlock;

    // Number of blocks after nSigmaMintStartBlock during which we still accept zerocoin V2 mints into mempool.
    int nZerocoinV2MintMempoolGracefulPeriod;

    // Number of blocks after nSigmaMintStartBlock during which we still accept zerocoin V2 mints to newly mined blocks.
    int nZerocoinV2MintGracefulPeriod;

    // Number of blocks after nSigmaMintStartBlock during which we still accept zerocoin V2 spend into mempool.
    int nZerocoinV2SpendMempoolGracefulPeriod;

    // Number of blocks after nSigmaMintStartBlock during which we still accept zerocoin V2 spend to newly mined blocks.
    int nZerocoinV2SpendGracefulPeriod;

    int64_t DifficultyAdjustmentInterval() const { return nPowTargetTimespan / nPowTargetSpacing; }
    uint256 nMinimumChainWork;

    // proof-of-stake
    int nLastPOWBlock;
    int nStakeTimestampMask;

    // Swap
    int nGenerateStopBlock;
};
} // namespace Consensus

#endif // BITCOIN_CONSENSUS_PARAMS_H
