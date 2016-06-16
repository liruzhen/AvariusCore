/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "naxxramas.h"

enum Spells
{
    SPELL_NECROTIC_AURA                     = 55593,
<<<<<<< HEAD
=======
    SPELL_WARN_NECROTIC_AURA                = 59481,
>>>>>>> origin/master
    SPELL_SUMMON_SPORE                      = 29234,
    SPELL_DEATHBLOOM                        = 29865,
    SPELL_INEVITABLE_DOOM                   = 29204,
    SPELL_FUNGAL_CREEP                      = 29232,

    SPELL_DEATHBLOOM_FINAL_DAMAGE           = 55594,
};

enum Texts
{
    SAY_NECROTIC_AURA_APPLIED       = 0,
    SAY_NECROTIC_AURA_REMOVED       = 1,
    SAY_NECROTIC_AURA_FADING        = 2,
};

enum Events
{
<<<<<<< HEAD
    EVENT_NECROTIC_AURA = 1,
    EVENT_DEATHBLOOM,
    EVENT_INEVITABLE_DOOM,
    EVENT_SPORE,
    EVENT_NECROTIC_AURA_FADING,
    EVENT_NECROTIC_AURA_FADED
=======
    EVENT_NECROTIC_AURA             = 1,
    EVENT_DEATHBLOOM                = 2,
    EVENT_INEVITABLE_DOOM           = 3,
    EVENT_SPORE                     = 4,
    EVENT_NECROTIC_AURA_FADING      = 5,
>>>>>>> origin/master
};

enum Achievement
{
    DATA_ACHIEVEMENT_SPORE_LOSER    = 21822183,
};

class boss_loatheb : public CreatureScript
{
    public:
        boss_loatheb() : CreatureScript("boss_loatheb") { }

        struct boss_loathebAI : public BossAI
        {
            boss_loathebAI(Creature* creature) : BossAI(creature, BOSS_LOATHEB)
            {
                Initialize();
            }

            void Initialize()
            {
                _doomCounter = 0;
                _sporeLoserData = true;
            }

            void Reset() override
            {
                _Reset();
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_FUNGAL_CREEP);
                Initialize();
            }

            void EnterCombat(Unit* /*who*/) override
            {
                _EnterCombat();
<<<<<<< HEAD
                events.ScheduleEvent(EVENT_NECROTIC_AURA, Seconds(17));
                events.ScheduleEvent(EVENT_DEATHBLOOM, Seconds(5));
                events.ScheduleEvent(EVENT_SPORE, Seconds(18));
                events.ScheduleEvent(EVENT_INEVITABLE_DOOM, Minutes(2));
=======
                events.ScheduleEvent(EVENT_NECROTIC_AURA, 17 * IN_MILLISECONDS);
                events.ScheduleEvent(EVENT_DEATHBLOOM, 5 * IN_MILLISECONDS);
                events.ScheduleEvent(EVENT_SPORE, RAID_MODE(36,18) * IN_MILLISECONDS);
                events.ScheduleEvent(EVENT_INEVITABLE_DOOM, 2 * MINUTE * IN_MILLISECONDS);
>>>>>>> origin/master
            }

            void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
            {
                _sporeLoserData = false;
                summon->CastSpell(summon,SPELL_FUNGAL_CREEP,true);
            }

<<<<<<< HEAD
=======
            void SummonedCreatureDespawn(Creature* summon) override
            {
                summons.Despawn(summon);
                if (summon->IsAlive())
                    summon->CastSpell(summon,SPELL_FUNGAL_CREEP,true);
            }

>>>>>>> origin/master
            uint32 GetData(uint32 id) const override
            {
                return (_sporeLoserData && id == DATA_ACHIEVEMENT_SPORE_LOSER) ? 1u : 0u;
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_NECROTIC_AURA:
                            DoCastAOE(SPELL_NECROTIC_AURA);
<<<<<<< HEAD
                            Talk(SAY_NECROTIC_AURA_APPLIED);
                            events.ScheduleEvent(EVENT_NECROTIC_AURA_FADING, Seconds(14));
                            events.ScheduleEvent(EVENT_NECROTIC_AURA_FADED, Seconds(17));
                            events.Repeat(Seconds(20));
                            break;
                        case EVENT_DEATHBLOOM:
                            DoCastAOE(SPELL_DEATHBLOOM);
                            events.Repeat(Seconds(30));
=======
                            DoCast(me, SPELL_WARN_NECROTIC_AURA);
                            events.ScheduleEvent(EVENT_NECROTIC_AURA, 20 * IN_MILLISECONDS);
                            events.ScheduleEvent(EVENT_NECROTIC_AURA_FADING, 14 * IN_MILLISECONDS);
                            break;
                        case EVENT_DEATHBLOOM:
                            DoCastAOE(SPELL_DEATHBLOOM);
                            events.ScheduleEvent(EVENT_DEATHBLOOM, 30 * IN_MILLISECONDS);
>>>>>>> origin/master
                            break;
                        case EVENT_INEVITABLE_DOOM:
                            _doomCounter++;
                            DoCastAOE(SPELL_INEVITABLE_DOOM);
                            if (_doomCounter > 6)
<<<<<<< HEAD
                                events.Repeat((_doomCounter & 1) ? Seconds(14) : Seconds(17));
                            else
                                events.Repeat(30);
                            break;
                        case EVENT_SPORE:
                            DoCast(me, SPELL_SUMMON_SPORE, false);
                            events.Repeat(RAID_MODE(Seconds(36), Seconds(15)));
=======
                            {
                                if (_doomCounter & 1) // odd
                                    events.ScheduleEvent(EVENT_INEVITABLE_DOOM, 14 * IN_MILLISECONDS);
                                else
                                    events.ScheduleEvent(EVENT_INEVITABLE_DOOM, 17 * IN_MILLISECONDS);
                            }
                            else
                                events.ScheduleEvent(EVENT_INEVITABLE_DOOM, 30 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPORE:
                            DoCast(me, SPELL_SUMMON_SPORE, false);
                            events.ScheduleEvent(EVENT_SPORE, RAID_MODE(36,18) * IN_MILLISECONDS);
>>>>>>> origin/master
                            break;
                        case EVENT_NECROTIC_AURA_FADING:
                            Talk(SAY_NECROTIC_AURA_FADING);
                            break;
<<<<<<< HEAD
                        case EVENT_NECROTIC_AURA_FADED:
                            Talk(SAY_NECROTIC_AURA_REMOVED);
                            break;
=======
>>>>>>> origin/master
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            bool _sporeLoserData;
            uint8 _doomCounter;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new boss_loathebAI(creature);
        }
};

class achievement_spore_loser : public AchievementCriteriaScript
{
    public:
        achievement_spore_loser() : AchievementCriteriaScript("achievement_spore_loser") { }

        bool OnCheck(Player* /*source*/, Unit* target) override
        {
            return target && target->GetAI()->GetData(DATA_ACHIEVEMENT_SPORE_LOSER);
        }
};

<<<<<<< HEAD
=======
typedef boss_loatheb::boss_loathebAI LoathebAI;

class spell_loatheb_necrotic_aura_warning : public SpellScriptLoader
{
    public:
        spell_loatheb_necrotic_aura_warning() : SpellScriptLoader("spell_loatheb_necrotic_aura_warning") { }

        class spell_loatheb_necrotic_aura_warning_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_loatheb_necrotic_aura_warning_AuraScript);

            bool Validate(SpellInfo const* /*spell*/) override
            {
                if (!sSpellStore.LookupEntry(SPELL_WARN_NECROTIC_AURA))
                    return false;
                return true;
            }

            void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget()->IsAIEnabled)
                    ENSURE_AI(LoathebAI, GetTarget()->GetAI())->Talk(SAY_NECROTIC_AURA_APPLIED);
            }

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget()->IsAIEnabled)
                    ENSURE_AI(LoathebAI, GetTarget()->GetAI())->Talk(SAY_NECROTIC_AURA_REMOVED);
            }

            void Register() override
            {
                AfterEffectApply += AuraEffectApplyFn(spell_loatheb_necrotic_aura_warning_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_loatheb_necrotic_aura_warning_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_loatheb_necrotic_aura_warning_AuraScript();
        }
};

>>>>>>> origin/master
class spell_loatheb_deathbloom : public SpellScriptLoader
{
    public:
        spell_loatheb_deathbloom() : SpellScriptLoader("spell_loatheb_deathbloom") { }

        class spell_loatheb_deathbloom_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_loatheb_deathbloom_AuraScript);

            bool Validate(SpellInfo const* /*spell*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DEATHBLOOM_FINAL_DAMAGE))
                    return false;
                return true;
            }

            void AfterRemove(AuraEffect const* eff, AuraEffectHandleModes /*mode*/)
            {
                if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
                    return;

                GetTarget()->CastSpell(nullptr, SPELL_DEATHBLOOM_FINAL_DAMAGE, true, nullptr, eff, GetCasterGUID());
            }

            void Register() override
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_loatheb_deathbloom_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_loatheb_deathbloom_AuraScript();
        }
};

void AddSC_boss_loatheb()
{
    new boss_loatheb();
    new achievement_spore_loser();
<<<<<<< HEAD
=======
    new spell_loatheb_necrotic_aura_warning();
>>>>>>> origin/master
    new spell_loatheb_deathbloom();
}
