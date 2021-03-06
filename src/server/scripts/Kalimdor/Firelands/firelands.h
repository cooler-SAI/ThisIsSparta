/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FIRELANDS_H_
#define FIRELANDS_H_

#include "Map.h"
#include "CreatureAI.h"

#define FirelandsScriptName "instance_firelands"

uint32 const EncounterCount = 7;

enum CreatureIds
{
	//Shannox
	BOSS_SHANNOX                    = 53691,
    
    NPC_RIPLIMB                     = 53694,
    NPC_RAGEFACE                    = 53695,
    NPC_SHANNOX_SPEAR               = 53752, 
    NPC_CRYSTAL_TRAP                = 53713,
    NPC_CRYSTAL_PRISON              = 53819,
    NPC_IMMOLATION_TRAP             = 53724,

    //Lord Rhyolith
	BOSS_RHYOLITH                   = 52558,

    LEFT_FOOT_RHYOLITH              = 52577,
    RIGHT_FOOT_RHYOLITH             = 53087,
    NPC_VOLCANO                     = 52582,
    NPC_CRATER                      = 52866,
    NPC_FRAGMENT_RHYOLITH           = 52620,
    NPC_SPARK_RHYOLITH              = 53211,
    NPC_LIQUID_OBSIDIAN             = 52619,

    //Beth'Tilac
	BOSS_BETHTILAC                  = 52498,

    NPC_CINDERWEB_SPINNER           = 52524,
    NPC_CINDERWEB_DRONE             = 52581,
    NPC_CINDERWEB_SPIDERLING        = 52447,
    NPC_ENGORGED_BROODLING          = 53745,	// Correct id?
    NPC_SPIDERWEB_FILAMENT          = 53082,	// This is the Elevator

    //Alysrazor
	BOSS_ALYSRAZOR                  = 52530,
    
    NPC_BLAZING_MONSTROSITY_LEFT    = 53786,
    NPC_BLAZING_MONSTROSITY_RIGHT   = 53791,
    NPC_EGG_PILE                    = 53795,
    NPC_HARBINGER_OF_FLAME          = 53793,
    NPC_MOLTEN_EGG_TRASH            = 53914,
    NPC_SMOULDERING_HATCHLING       = 53794,

    //Baleroc
	BOSS_BALEROC                    = 53494,

    NPC_SHARD_OF_TORMENT            = 53495,

    //Majordomo Staghelm
	BOSS_MAJORDOMO_STAGHELM         = 52571,

    NPC_SPIRIT_OF_THE_FLAME         = 52593,

    //Ragnaros
    BOSS_RAGNAROS                   = 52409,

    NPC_ENGULFING_FLAMES_TRIGGER    = 53485,
    NPC_SPLITTING_BLOW_TRIGGER      = 53393,
    NPC_MAGMA_POOL_TRIGGER          = 53729,
    NPC_PLATFORM_TRIGGER            = 53952,
    NPC_MAGMA_TRAP                  = 53086,
    NPC_SULFURAS_HAMMER             = 53420,
    NPC_SULFURAS_FLAME_WALL         = 38327,
    NPC_SULFURAS_SMASH_TARGET_1     = 53268,
    NPC_LAVA_WAVE                   = 53363,
    NPC_SON_OF_FLAME                = 53140,
    NPC_LIVING_METEOR               = 53500,
    NPC_MOLTEN_ELEMENTAR            = 53189,
};

enum PathIDs
{
	PATH_SHANNOX = 154280940,
};

enum DataVar
{
DATA_PHASE,
};

enum Data
{
	DATA_SHANNOX_EVENT,
	DATA_RHYOLITH_EVENT,
	DATA_BETHTILAC_EVENT,
	DATA_ALYSRAZOR_EVENT,
	DATA_BALEROC_EVENT,
	DATA_MAJORDOMO_STAGHELM_EVENT,
	DATA_RAGNAROS_EVENT,
	DATA_TEAM_IN_INSTANCE,

    DATA_CURRENT_ENCOUNTER_PHASE,
    DATA_SHARD_OF_TORMENT,
};

Position const shannoxspawn =  {-241.456f,103.116f,47.8124f,1.50341f};

enum Data64
{
	DATA_SHANNOX,
	DATA_RHYOLITH,
	DATA_BETHTILAC,
	DATA_ALYSRAZOR,
	DATA_BALEROC,
	DATA_MAJORDOMO_STAGHELM,
	DATA_RAGNAROS,
};
enum GameObjectIds
{
    GO_RAGNAROS_DOOR            = 209073,
    GO_RAGNAROS_PLATFORM        = 208835,
    GO_CACHE_OF_THE_FIRELORD    = 208967,
};

/*enum DataTypes
{
    DATA_BETH_TILAC         = 0,
    DATA_LORD_RHYOLITH      = 1,
    DATA_SHANNOX            = 2,
    DATA_ALYSRAZOR          = 3,
    DATA_BALEROC            = 4,
    DATA_MAJORDOMO_STAGHELM = 5,
    DATA_RAGNAROS           = 6,
};*/

enum Phase
{
    //Shannox
    PHASE_NON = 0,

    PHASE_SHANNOX_HAS_SPEER = 1,
    PHASE_SPEAR_ON_THE_GROUND = 2,
    PHASE_RIPLIMB_GOS_TO_SPEER = 3,
    PHASE_RIPLIMB_BRINGS_SPEER = 4,

    // Bethilac
    PHASE_BETHILAC_UPPER = 5,
    PHASE_BETHILAC_LOWER = 6,



};

class DelayedAttackStartEvent : public BasicEvent
{
    public:
        DelayedAttackStartEvent(Creature* owner) : _owner(owner) { }

        bool Execute(uint64 /*e_time*/, uint32 /*p_time*/)
        {
            _owner->AI()->DoZoneInCombat(_owner, 200.0f);
            return true;
        }

    private:
        Creature* _owner;
};

template<class AI>
CreatureAI* GetFirelandsAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId(FirelandsScriptName))
                return new AI(creature);
    return NULL;
}

#endif // FIRELANDS_H_
