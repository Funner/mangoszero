/*
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2010 MaNGOSZero <http://github.com/mangoszero/mangoszero/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ObjectMgr.h"                                      // for normalizePlayerName
#include "ChannelMgr.h"

void WorldSession::HandleJoinChannel(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());

    uint32 channel_id = 0;
    std::string channelname, pass;

    recvPacket >> channelname;

    if(channelname.empty())
        return;

    recvPacket >> pass;
    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetJoinChannel(channelname, channel_id)) // channel id seems to be useless but must be checked for LFG
            chn->Join(_player->GetGUID(), pass.c_str());
}

void WorldSession::HandleLeaveChannel(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    // uint32 unk;
    std::string channelname;
    // recvPacket >> unk;                                      // channel id?
    recvPacket >> channelname;

    if(channelname.empty())
        return;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
    {
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->Leave(_player->GetGUID(), true);
        cMgr->LeftChannel(channelname);
    }
}

void WorldSession::HandleChannelList(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname;
    recvPacket >> channelname;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->List(_player);
}

void WorldSession::HandleChannelPassword(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname, pass;
    recvPacket >> channelname;

    recvPacket >> pass;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->Password(_player->GetGUID(), pass.c_str());
}

void WorldSession::HandleChannelSetOwner(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();

    std::string channelname, newp;
    recvPacket >> channelname;

    recvPacket >> newp;

    if(!normalizePlayerName(newp))
        return;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->SetOwner(_player->GetGUID(), newp.c_str());
}

void WorldSession::HandleChannelOwner(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname;
    recvPacket >> channelname;
    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->SendWhoOwner(_player->GetGUID());
}

void WorldSession::HandleChannelModerator(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname, otp;
    recvPacket >> channelname;

    recvPacket >> otp;

    if(!normalizePlayerName(otp))
        return;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->SetModerator(_player->GetGUID(), otp.c_str());
}

void WorldSession::HandleChannelUnmoderator(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname, otp;
    recvPacket >> channelname;

    recvPacket >> otp;

    if(!normalizePlayerName(otp))
        return;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->UnsetModerator(_player->GetGUID(), otp.c_str());
}

void WorldSession::HandleChannelMute(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname, otp;
    recvPacket >> channelname;

    recvPacket >> otp;

    if(!normalizePlayerName(otp))
        return;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->SetMute(_player->GetGUID(), otp.c_str());
}

void WorldSession::HandleChannelUnmute(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname, otp;
    recvPacket >> channelname;

    recvPacket >> otp;

    if(!normalizePlayerName(otp))
        return;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->UnsetMute(_player->GetGUID(), otp.c_str());
}

void WorldSession::HandleChannelInvite(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname, otp;
    recvPacket >> channelname;

    recvPacket >> otp;

    if(!normalizePlayerName(otp))
        return;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->Invite(_player->GetGUID(), otp.c_str());
}

void WorldSession::HandleChannelKick(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname, otp;
    recvPacket >> channelname;

    recvPacket >> otp;
    if(!normalizePlayerName(otp))
        return;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->Kick(_player->GetGUID(), otp.c_str());
}

void WorldSession::HandleChannelBan(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname, otp;
    recvPacket >> channelname;

    recvPacket >> otp;

    if(!normalizePlayerName(otp))
        return;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->Ban(_player->GetGUID(), otp.c_str());
}

void WorldSession::HandleChannelUnban(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname, otp;
    recvPacket >> channelname;

    recvPacket >> otp;

    if(!normalizePlayerName(otp))
        return;

    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->UnBan(_player->GetGUID(), otp.c_str());
}

void WorldSession::HandleChannelAnnouncements(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname;
    recvPacket >> channelname;
    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->Announce(_player->GetGUID());
}

void WorldSession::HandleChannelModerate(WorldPacket& recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname;
    recvPacket >> channelname;
    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->Moderate(_player->GetGUID());
}

void WorldSession::HandleChannelDisplayListQuery(WorldPacket &recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname;
    recvPacket >> channelname;
    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->List(_player);
}

void WorldSession::HandleGetChannelMemberCount(WorldPacket &recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname;
    recvPacket >> channelname;
    if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
    {
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
        {
            WorldPacket data(SMSG_CHANNEL_MEMBER_COUNT, chn->GetName().size()+1+1+4);
            data << chn->GetName();
            data << uint8(chn->GetFlags());
            data << uint32(chn->GetNumPlayers());
            SendPacket(&data);
        }
    }
}

void WorldSession::HandleSetChannelWatch(WorldPacket &recvPacket)
{
    DEBUG_LOG("Opcode %u", recvPacket.GetOpcode());
    //recvPacket.hexlike();
    std::string channelname;
    recvPacket >> channelname;
    /*if(ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if(Channel *chn = cMgr->GetChannel(channelname, _player))
            chn->JoinNotify(_player->GetGUID());*/
}
