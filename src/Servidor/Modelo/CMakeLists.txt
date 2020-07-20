project(argentum)

include_directories(Commands)
include_directories(Equippables)

set(CHARACTERSSRCS
        Character/Alive.h
        Character/Alive.cpp
        Character/Armour.h
        Character/Armour.cpp
        Character/BankAccount.h
        Character/BankAccount.cpp
        Character/Banker.h
        Character/Banker.cpp
        Character/Character.h
        Character/Character.cpp
        Character/Ghost.h
        Character/Ghost.cpp
        Character/Inventory.h
        Character/Inventory.cpp
        Character/ItemSeller.h
        Character/ItemSeller.cpp
        Character/LifeState.h
        Character/Meditating.h
        Character/Meditating.cpp
        Character/MeditationState.h
        Character/Merchant.h
        Character/Merchant.cpp
        Character/NotMeditating.h
        Character/NotMeditating.cpp
        Character/Npc.h
        Character/Npc.cpp
        Character/PlayableCharacter.h
        Character/PlayableCharacter.cpp
        Character/Priest.h
        Character/Priest.cpp)

set(COMMANDSSRCS
        Commands/Command.h
        Commands/BuyCommand.h
        Commands/BuyCommand.cpp
        Commands/CommandExecutor.h
        Commands/CommandExecutor.cpp
        Commands/DepositCommand.h
        Commands/DepositCommand.cpp
        Commands/ExtractCommand.h
        Commands/ExtractCommand.cpp
        Commands/HealCommand.h
        Commands/HealCommand.cpp
        Commands/ListItemsCommand.h
        Commands/ListItemsCommand.cpp
        Commands/MeditateCommand.h
        Commands/MeditateCommand.cpp
        Commands/PrivateMessageCommand.h
        Commands/PrivateMessageCommand.cpp
        Commands/ReviveCommand.h
        Commands/ReviveCommand.cpp
        Commands/SellCommand.h
        Commands/SellCommand.cpp
        Commands/TakeItemCommand.h
        Commands/TakeItemCommand.cpp
        Commands/DropItemCommand.h
        Commands/DropItemCommand.cpp)

set(EQUIPPABLESSRCS
        Equippables/Equippable.h
        Equippables/Equippable.cpp
        Equippables/LifePotion.h
        Equippables/LifePotion.cpp
        Equippables/MagicalWeapon.h
        Equippables/MagicalWeapon.cpp
        Equippables/ManaPotion.h
        Equippables/ManaPotion.cpp
        Equippables/NormalWeapon.h
        Equippables/NormalWeapon.cpp
        Equippables/Potion.h
        Equippables/Potion.cpp
        Equippables/Protection.h
        Equippables/Protection.cpp
        Equippables/RangeWeapon.h
        Equippables/RangeWeapon.cpp
        Equippables/Weapon.h
        Equippables/Weapon.cpp)

set(DROPPABLESSRCS
        Dropppables/Drop.h
        Dropppables/Drop.cpp
        Dropppables/Droppable.h
        Dropppables/GoldBag.h
        Dropppables/GoldBag.cpp
        )

set(MAPSSRCS
        Map/City.h
        Map/City.cpp
        Map/Map.h
        Map/Map.cpp
        Map/Obstacle.h
        Map/Obstacle.cpp
        Map/Offset.h
        Map/Offset.cpp
        Map/Position.h
        Map/Position.cpp)

set(SPELLSSRCS
        Spells/Damage.h
        Spells/Damage.cpp
        Spells/Heal.h
        Spells/Heal.cpp
        Spells/SpellType.h)



FILE(GLOB SRCS *.cpp *.h)

add_library(servidorModeloLib ${SRCS}
                                ${CHARACTERSSRCS}
                                ${COMMANDSSRCS}
                                ${EQUIPPABLESSRCS}
                                ${DROPPABLESSRCS}
                                ${MAPSSRCS}
                                ${SPELLSSRCS})