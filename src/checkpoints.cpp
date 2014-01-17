// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 ekrona Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //

    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, hashGenesisBlockOfficial )
            (   350, uint256("0x0c8113371320dc69d22f6171e3a9fe97337fc95a1a36313135a786829311688e"))
            (   850, uint256("0x8d8a9052be32078892ae3809b3e5650801fdc48408339aa334ec847777602962"))
            (  1774, uint256("0x1acb91c57eaf2c9ca2542a8fe4a796abf60e930cd8a6eb7f3356b870e0eea0e9"))
            (  2055, uint256("0x274ef8414482dd81428a77af6ca7dbaae7c949ef55ee7d05f0aace0a3885ad80"))
            (  2710, uint256("0xc64be3a87e8994d1e0dee6421e3063315a9de22dbde29c914acd951d7c8d2c1c"))
            (  3350, uint256("0x9f20a1e051a55e3dece049b8586c7376682347720c7ee3daeda95b80367c047e"))
			;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
		// return true;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
		// return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
				// return NULL;
        }
        return NULL;
    }
}
