#include "ScriptPCH.h"

/*******************************************************
 * NPC Vendedor de Reliquias (Heirlooms)
 * ScriptName: npc_heirloom
 *******************************************************/

class npc_heirloom : public CreatureScript
{
public:
    npc_heirloom() : CreatureScript("npc_heirloom") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        // Menú Principal
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\Icons\\INV_Sword_04:30:30:-18:0|t Armas", GOSSIP_SENDER_MAIN, 100);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\Icons\\INV_Chest_Plate04:30:30:-18:0|t Placas", GOSSIP_SENDER_MAIN, 200);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\Icons\\INV_Chest_Chain_03:30:30:-18:0|t Malla", GOSSIP_SENDER_MAIN, 300);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\Icons\\INV_Chest_Leather_08:30:30:-18:0|t Cuero", GOSSIP_SENDER_MAIN, 400);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\Icons\\INV_Chest_Cloth_23:30:30:-18:0|t Tela", GOSSIP_SENDER_MAIN, 500);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\Icons\\INV_Jewelry_Ring_05:30:30:-18:0|t Otros", GOSSIP_SENDER_MAIN, 600);
        
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        // Si la accion es mayor a 1000, asumimos que es un ID de item para entregar
        if (action > 1000)
        {
            AddItem(player, action);
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        switch (action)
        {
            case 100: // Armas
                // Hachas
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hacha 2M (Fuerza) - Bloodied Arcanite Reaper", GOSSIP_SENDER_MAIN, 42943);
                // Mazas
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Maza 2M (Fuerza) - Repurposed Lava Dredger", GOSSIP_SENDER_MAIN, 48718);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Maza 1M (Intelecto) - Devout Aurastone Hammer", GOSSIP_SENDER_MAIN, 42948);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Maza 1M (Intelecto) - The Blessed Hammer of Grace", GOSSIP_SENDER_MAIN, 44094);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Maza 1M (Agilidad) - Venerable Mass of McGowan", GOSSIP_SENDER_MAIN, 48716);
                // Bastones
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Baston (Intelecto) - Dignified Headmaster's Charge", GOSSIP_SENDER_MAIN, 42947);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Baston (Intelecto) - Grand Staff of Jordan", GOSSIP_SENDER_MAIN, 44095);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Baston (Agilidad) - Burnished Warden Staff", GOSSIP_SENDER_MAIN, 44092);
                // Arcos / Rifles
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Arco (Agilidad) - Charmed Ancient Bone Bow", GOSSIP_SENDER_MAIN, 42946);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Rifle (Agilidad) - Upgraded Dwarven Hand Cannon", GOSSIP_SENDER_MAIN, 44093);
                // Dagas
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Daga (Agilidad) - Balanced Heartseeker", GOSSIP_SENDER_MAIN, 42944);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Daga (Agilidad) - Sharpened Scarlet Kris", GOSSIP_SENDER_MAIN, 44091);
                // Espadas
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Espada 1M (Fuerza) - Venerable Dal'Rend's Sacred Charge", GOSSIP_SENDER_MAIN, 42945);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Espada 1M (Agilidad) - Battleworn Thrash Blade", GOSSIP_SENDER_MAIN, 44096);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Espada 2M (Fuerza) - Reforged Truesilver Champion", GOSSIP_SENDER_MAIN, 44092);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Espada 2M (Fuerza) - Ancestral Claymore", GOSSIP_SENDER_MAIN, 38691);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Espada 1M (Fuerza) - Bloodsoaked Skullforge Reaver", GOSSIP_SENDER_MAIN, 69893);
                
                AddBackOption(player);
                break;

            case 200: // Placas
                // Valor (Fuerza)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Casco (Fuerza) - Polished Helm of Valor", GOSSIP_SENDER_MAIN, 61931);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hombros (Fuerza) - Polished Spaulders of Valor", GOSSIP_SENDER_MAIN, 42949);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Pecho (Fuerza) - Polished Breastplate of Valor", GOSSIP_SENDER_MAIN, 48685);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Piernas (Fuerza) - Polished Legplates of Valor", GOSSIP_SENDER_MAIN, 62023);
                // Might (Fuerza)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Casco (Fuerza) - Burnished Helm of Might", GOSSIP_SENDER_MAIN, 69887);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Piernas (Fuerza) - Burnished Legplates of Might", GOSSIP_SENDER_MAIN, 69888);
                // Otros
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hombros (Defensa) - Strengthened Stockade Pauldrons", GOSSIP_SENDER_MAIN, 44099);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Casco (Intelecto) - Pristine Lightforge Helm", GOSSIP_SENDER_MAIN, 61935);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hombros (Intelecto) - Pristine Lightforge Spaulders", GOSSIP_SENDER_MAIN, 44100);
                
                AddBackOption(player);
                break;

            case 300: // Malla
                // Elements (Intelecto)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Casco (Intelecto) - Mystical Coif of Elements", GOSSIP_SENDER_MAIN, 61936);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hombros (Intelecto) - Mystical Pauldrons of Elements", GOSSIP_SENDER_MAIN, 42951);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Pecho (Intelecto) - Mystical Vest of Elements", GOSSIP_SENDER_MAIN, 48683);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Piernas (Intelecto) - Mystical Kilt of Elements", GOSSIP_SENDER_MAIN, 62025);
                // Beastmaster (Agilidad)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Casco (Agilidad) - Tarnished Raging Berserker's Helm", GOSSIP_SENDER_MAIN, 61935);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hombros (Agilidad) - Champion Herod's Shoulder", GOSSIP_SENDER_MAIN, 42950);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hombros (Agilidad) - Prized Beastmaster's Mantle", GOSSIP_SENDER_MAIN, 44101);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Pecho (Agilidad) - Champion's Deathdealer Breastplate", GOSSIP_SENDER_MAIN, 48677);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Piernas (Agilidad) - Tarnished Leggings of Destruction", GOSSIP_SENDER_MAIN, 62024);
                
                AddBackOption(player);
                break;

            case 400: // Cuero
                // Shadowcraft (Agilidad)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Casco (Agilidad) - Stained Shadowcraft Cap", GOSSIP_SENDER_MAIN, 61937);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hombros (Agilidad) - Stained Shadowcraft Spaulders", GOSSIP_SENDER_MAIN, 42952);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Pecho (Agilidad) - Stained Shadowcraft Tunic", GOSSIP_SENDER_MAIN, 48689);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Piernas (Agilidad) - Stained Shadowcraft Pants", GOSSIP_SENDER_MAIN, 62026);
                // Ironfeather (Intelecto/Druida)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Casco (Intelecto) - Preened Tribal War Feathers", GOSSIP_SENDER_MAIN, 61942);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hombros (Intelecto) - Preened Ironfeather Shoulders", GOSSIP_SENDER_MAIN, 42984);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Pecho (Intelecto) - Preened Ironfeather Breastplate", GOSSIP_SENDER_MAIN, 48687);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Piernas (Intelecto) - Preened Wildfeather Leggings", GOSSIP_SENDER_MAIN, 62027);
                
                AddBackOption(player);
                break;

            case 500: // Tela
                // Dreadmist
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Casco (Intelecto) - Tattered Dreadmist Mask", GOSSIP_SENDER_MAIN, 61958);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hombros (Intelecto) - Tattered Dreadmist Mantle", GOSSIP_SENDER_MAIN, 42985);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Pecho (Intelecto) - Tattered Dreadmist Robe", GOSSIP_SENDER_MAIN, 44105);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Piernas (Intelecto) - Tattered Dreadmist Leggings", GOSSIP_SENDER_MAIN, 62029);
                // Otros Tela? No, just Dreadmist usually.
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hombros (Intelecto) - Exquisite Sunderseer Mantle", GOSSIP_SENDER_MAIN, 44107);
                
                AddBackOption(player);
                break;
                
            case 600: // Otros
                // Faccion Check
                if (player->GetTeamId() == TEAM_HORDE)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Abalorio (PvP) - Inherited Insignia of the Horde", GOSSIP_SENDER_MAIN, 44097);
                else
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Abalorio (PvP) - Inherited Insignia of the Alliance", GOSSIP_SENDER_MAIN, 44098);
                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Abalorio (Haste/Health) - Swift Hand of Justice", GOSSIP_SENDER_MAIN, 42991);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Abalorio (Mana/Health) - Discerning Eye of the Beast", GOSSIP_SENDER_MAIN, 42992);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Anillo (XP) - Dread Pirate Ring", GOSSIP_SENDER_MAIN, 50255);
                
                // Capas
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Capa (Fuerza/Tank) - Worn Stoneskin Gargoyle Cape", GOSSIP_SENDER_MAIN, 62038);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Capa (Agilidad) - Inherited Cape of the Black Baron", GOSSIP_SENDER_MAIN, 62039);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Capa (Intelecto) - Ancient Bloodmoon Cloak", GOSSIP_SENDER_MAIN, 62040);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Capa (Fuerza/DPS) - Ripped Sandstorm Cloak", GOSSIP_SENDER_MAIN, 69892);
                
                AddBackOption(player);
                break;

            case 999: // Volver
                OnGossipHello(player, creature);
                break;
        }
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    void AddBackOption(Player* player)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "<- Volver", GOSSIP_SENDER_MAIN, 999);
    }

    void AddItem(Player* player, uint32 itemId)
    {
        ItemPosCountVec dest;
        InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, 1);
        if (msg == EQUIP_ERR_OK)
        {
            player->StoreNewItem(dest, itemId, true);
            player->GetSession()->SendNotification("Has recibido una reliquia!");
            // player->GetSession()->SendAreaTriggerMessage("Item agregado!");
        }
        else
            player->SendEquipError(msg, NULL, NULL, itemId);
    }
};

void AddSC_npc_heirloom()
{
    new npc_heirloom();
}
