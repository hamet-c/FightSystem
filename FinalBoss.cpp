#include "FinalBoss.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

Player CreateVoidstormPhase1() {
	Player boss("The Voidstorm", 300, 20, 0, -1);
	Attacks bossAttacks;

	Attack runAway = Attack();
	runAway.SetName("Dark Retreat");
	runAway.SetDesc("The Voidstorm pulls back, absorbing ambient energy");
	bossAttacks.AssignAttack(runAway);

	Attack voidPulse("Void Pulse", 15, "A pulse of dark energy", 3);
	voidPulse.SetMinDamage(12); voidPulse.SetMaxDamage(18);
	bossAttacks.AssignAttack(voidPulse);

	Attack stormDrain("Storm Drain", 11, "Drains the storm energy around you", 4);
	stormDrain.SetMinDamage(8); stormDrain.SetMaxDamage(14);
	stormDrain.SetCooldownTurns(1);
	stormDrain.SetStatusEffect("poison"); stormDrain.SetStatusDuration(2); stormDrain.SetStatusDamagePerTurn(3);
	bossAttacks.AssignAttack(stormDrain);

	Attack thunderCage("Thunder Cage", 24, "Imprisons you in a cage of stolen lightning", 5);
	thunderCage.SetMinDamage(20); thunderCage.SetMaxDamage(28);
	thunderCage.SetCooldownTurns(2);
	thunderCage.SetStatusEffect("stun"); thunderCage.SetStatusDuration(1);
	bossAttacks.AssignAttack(thunderCage);

	Attack nullField("Null Field", 10, "A field that dampens all energy around it", 6);
	nullField.SetMinDamage(8); nullField.SetMaxDamage(12);
	nullField.SetCooldownTurns(2);
	nullField.SetStatusEffect("poison"); nullField.SetStatusDuration(2); nullField.SetStatusDamagePerTurn(5);
	bossAttacks.AssignAttack(nullField);

	boss.AssignPlayerAttacks(bossAttacks);
	return boss;
}

Player CreateVoidstormPhase2() {
	Player boss("Voidstorm Unleashed", 200, 25, 0, -1);
	Attacks bossAttacks;

	Attack runAway = Attack();
	runAway.SetName("Consume Ambient Storm");
	runAway.SetDesc("The Voidstorm feeds on the storm around it");
	bossAttacks.AssignAttack(runAway);

	Attack voidSlash("Void Slash", 19, "A devastating slash of pure void energy", 3);
	voidSlash.SetMinDamage(15); voidSlash.SetMaxDamage(22);
	bossAttacks.AssignAttack(voidSlash);

	Attack oblivionBolt("Oblivion Bolt", 29, "A bolt of pure nothingness that tears at your body", 4);
	oblivionBolt.SetMinDamage(25); oblivionBolt.SetMaxDamage(32);
	oblivionBolt.SetCooldownTurns(1);
	oblivionBolt.SetStatusEffect("bleed"); oblivionBolt.SetStatusDuration(2); oblivionBolt.SetStatusDamagePerTurn(5);
	bossAttacks.AssignAttack(oblivionBolt);

	Attack worldEnder("World Ender", 48, "The attack that ends worlds", 5);
	worldEnder.SetMinDamage(40); worldEnder.SetMaxDamage(55);
	worldEnder.SetCooldownTurns(3);
	worldEnder.SetCritChance(0.15f);
	bossAttacks.AssignAttack(worldEnder);

	Attack consumeStorm("Consume Storm", 35, "Devours the storm itself, growing stronger", 6);
	consumeStorm.SetMinDamage(30); consumeStorm.SetMaxDamage(40);
	consumeStorm.SetCooldownTurns(2);
	consumeStorm.SetStatusEffect("stun"); consumeStorm.SetStatusDuration(1);
	bossAttacks.AssignAttack(consumeStorm);

	boss.AssignPlayerAttacks(bossAttacks);
	return boss;
}

void EvolveHeroAttacks(Player& hero, int weaponChoice) {
	Attacks evolvedAttacks;
	Attack runAway = Attack();
	evolvedAttacks.AssignAttack(runAway);

	Attack punch("Punch", 5, "A quick strike", 3);
	punch.SetMinDamage(4); punch.SetMaxDamage(6);
	evolvedAttacks.AssignAttack(punch);

	if (weaponChoice == 1) {
		// Thunder Fang -> Tempest Fang (wind/pressure attacks)
		Attack tempestSlash("Tempest Slash", 24, "A blade wreathed in hurricane winds cleaves through the enemy", 4);
		tempestSlash.SetMinDamage(20); tempestSlash.SetMaxDamage(28);
		tempestSlash.SetIsLightning(false);
		evolvedAttacks.AssignAttack(tempestSlash);

		Attack galeForce("Gale Force", 34, "Unleash the full fury of a gale-force wind", 5);
		galeForce.SetMinDamage(30); galeForce.SetMaxDamage(38);
		galeForce.SetCooldownTurns(1);
		galeForce.SetCritChance(0.20f);
		galeForce.SetStatusEffect("bleed"); galeForce.SetStatusDuration(2); galeForce.SetStatusDamagePerTurn(3);
		galeForce.SetIsLightning(false);
		evolvedAttacks.AssignAttack(galeForce);

		Attack cataclysm("Cataclysm", 53, "The full fury of the storm made manifest", 6);
		cataclysm.SetMinDamage(45); cataclysm.SetMaxDamage(60);
		cataclysm.SetCooldownTurns(3);
		cataclysm.SetCritChance(0.30f);
		cataclysm.SetIsLightning(false);
		evolvedAttacks.AssignAttack(cataclysm);
	}
	else {
		// Sky Piercers -> Stormbreaker Blades (cyclone attacks)
		Attack cycloneStrike("Cyclone Strike", 21, "Spinning blades create a miniature cyclone", 4);
		cycloneStrike.SetMinDamage(18); cycloneStrike.SetMaxDamage(24);
		cycloneStrike.SetIsLightning(false);
		evolvedAttacks.AssignAttack(cycloneStrike);

		Attack hurricaneFangs("Hurricane Fangs", 29, "The daggers trail vortexes of wind toxin", 5);
		hurricaneFangs.SetMinDamage(25); hurricaneFangs.SetMaxDamage(32);
		hurricaneFangs.SetCooldownTurns(1);
		hurricaneFangs.SetStatusEffect("poison"); hurricaneFangs.SetStatusDuration(2); hurricaneFangs.SetStatusDamagePerTurn(6);
		hurricaneFangs.SetIsLightning(false);
		evolvedAttacks.AssignAttack(hurricaneFangs);

		Attack eyeOfStorm("Eye of the Storm", 48, "Strike from the calm center of absolute destruction", 6);
		eyeOfStorm.SetMinDamage(40); eyeOfStorm.SetMaxDamage(55);
		eyeOfStorm.SetCooldownTurns(3);
		eyeOfStorm.SetCritChance(0.25f);
		eyeOfStorm.SetStatusEffect("stun"); eyeOfStorm.SetStatusDuration(1);
		eyeOfStorm.SetIsLightning(false);
		evolvedAttacks.AssignAttack(eyeOfStorm);
	}

	hero.AssignPlayerAttacks(evolvedAttacks);
}

void NarrateReveal(Game& game, Player& hero) {
	game.SpaceMax();
	game.WriteSentenceNoEndl("Shadow Being: You have proven your worthiness, hero.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: But the trial was merely preparation for what awaits.");
	cout << endl << endl;
	this_thread::sleep_for(chrono::seconds(3));

	cout << "*The Shadow Being's form flickers, and for the first time you see fear in its void-like face*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	game.WriteSentenceNoEndl("Shadow Being: There is an ancient entity... older than me, older than the storms themselves.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: It is called The Voidstorm -- the Eater of Storms.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: For millennia it has been sealed away, feeding on the electrical energy of the world.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: But the seal is breaking. It will consume all lightning, all storms, all life.");
	cout << endl << endl;
	this_thread::sleep_for(chrono::seconds(3));

	cout << hero.GetName() << ": Then I'll stop it. I have the power of Kael Thunderborn--" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << endl;

	game.WriteSentenceNoEndl("Shadow Being: FOOL. That is precisely why YOU are in danger.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: The Voidstorm FEEDS on lightning. Your ancestor's power... is its food.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: You must find another way. Adapt. Evolve. Or perish.");
	cout << endl << endl;
	this_thread::sleep_for(chrono::seconds(3));

	cout << "*The Shadow Being strikes the ground. A massive rift tears open in the cave wall.*" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "*Through it, you see a sky of pure darkness, crackling with stolen lightning.*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	game.WriteSentenceNoEndl("Shadow Being: Go now. The Voidstorm awaits at the heart of the storm.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: Remember -- lightning alone will not save you.");
	cout << endl << endl;
	this_thread::sleep_for(chrono::seconds(3));

	game.SpaceMax();

	cout << "*You step through the rift...*" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "*The air is thick with static. The ground trembles beneath your feet.*" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "*Before you stands a massive swirling vortex of darkness and captured lightning.*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << "???: You... you carry the scent of storms." << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "???: How DELICIOUS." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << "*The vortex coalesces into a towering humanoid figure crackling with absorbed lightning*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;
	cout << "THE VOIDSTORM: Come, little spark. Let me CONSUME you." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;
}

void NarrateEvolution(Game& game, Player& hero, int weaponChoice) {
	game.SpaceMax();

	cout << "*The Voidstorm collapses... then begins to reform, darker and more powerful than before*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << "THE VOIDSTORM: Impressive... but you cannot kill what feeds on the storm." << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "THE VOIDSTORM: Every bolt you throw only makes me STRONGER." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	if (weaponChoice == 1) {
		cout << "*You feel your Thunder Fang vibrating in your hands*" << endl;
	}
	else {
		cout << "*You feel your Sky Piercers vibrating in your hands*" << endl;
	}
	this_thread::sleep_for(chrono::seconds(2));

	cout << "*A voice echoes in your mind -- the voice of Kael Thunderborn*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	game.WriteSentenceNoEndl("Kael: Descendant... lightning is but ONE face of the storm.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Kael: The storm is wind. The storm is pressure. The storm is fury itself.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Kael: Do not fight WITH the lightning. Fight with the STORM.");
	cout << endl << endl;
	this_thread::sleep_for(chrono::seconds(3));

	cout << "*Your weapon begins to transform*" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "*The crackling electricity fades, replaced by howling winds and crushing pressure*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	if (weaponChoice == 1) {
		cout << "*Thunder Fang becomes TEMPEST FANG -- a blade wreathed in hurricane winds*" << endl;
	}
	else {
		cout << "*Sky Piercers become STORMBREAKER BLADES -- daggers trailing cyclone vortexes*" << endl;
	}
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << hero.GetName() << ": I understand now. I am not just a wielder of lightning." << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << hero.GetName() << ": I am the STORM." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << "*New abilities unlocked!*" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << endl;

	cout << "THE VOIDSTORM: What... what is this? This power... it is not lightning!" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "THE VOIDSTORM: No matter. I will CRUSH you regardless!" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;
}

void NarrateVictory(Game& game, Player& hero) {
	game.SpaceMax();

	cout << "*The Voidstorm lets out a deafening shriek as your final blow connects*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << "THE VOIDSTORM: IMPOSSIBLE... the storm... was supposed to be MINE..." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << "*The entity begins to dissolve, the stolen lightning dispersing back into the sky*" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "*The darkness recedes. For the first time, you see sunlight breaking through the clouds.*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << "*You fall to your knees, exhausted but alive.*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << "*The rift reopens. The Shadow Being steps through.*" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << endl;

	game.WriteSentenceNoEndl("Shadow Being: ...You did it.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: You have done what even Kael Thunderborn could not.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: You did not just wield the storm -- you BECAME it.");
	cout << endl << endl;
	this_thread::sleep_for(chrono::seconds(3));

	cout << hero.GetName() << ": I had help. From Kael. From you." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	game.WriteSentenceNoEndl("Shadow Being: The world is safe once more. The storms will return to their natural state.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: And you... you are no longer just a descendant.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: You are the new Thunderborn. No -- you are something greater.");
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
	game.WriteSentenceNoEndl("Shadow Being: You are the Stormborn.");
	cout << endl << endl;
	this_thread::sleep_for(chrono::seconds(3));

	cout << "*The Shadow Being bows -- something you never thought you'd see.*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	game.WriteSentenceNoEndl("Shadow Being: Go now, Stormborn. The world awaits its hero.");
	cout << endl << endl;
	this_thread::sleep_for(chrono::seconds(3));

	cout << "*You step back through the rift, into the sunlight.*" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "*The storms above you part, and for the first time in what feels like forever...*" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "*There is peace.*" << endl;
	this_thread::sleep_for(chrono::seconds(3));

	cout << endl << endl;
	cout << "              === THE END ===" << endl;
	cout << "     Thank you for playing, " << hero.GetName() << "." << endl;
	cout << endl << endl;
}

void NarrateDefeat(Game& game) {
	game.SpaceMax();

	cout << "*Your vision fades as The Voidstorm's power overwhelms you*" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << "THE VOIDSTORM: Another spark... extinguished." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	cout << "*The world goes dark.*" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "*The storms rage on, unchecked, eternal.*" << endl;
	this_thread::sleep_for(chrono::seconds(3));

	cout << endl << endl;
	cout << "              === GAME OVER ===" << endl;
	cout << "     The Voidstorm consumes the world in darkness." << endl;
	cout << endl << endl;
}

void FinalBossSequence(Game& game, Player& hero, int weaponChoice) {
	// Narrative: Shadow Being reveals the threat
	NarrateReveal(game, hero);

	// Phase 1: Fight the Storm Devourer
	Player boss1 = CreateVoidstormPhase1();

	cout << "=== PHASE 1: THE STORM DEVOURER ===" << endl;
	cout << "WARNING: Your lightning attacks will be absorbed!" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	// Show hero's current attacks
	cout << "Your current attacks:" << endl;
	cout << "1) Default attack (damage: " << hero.GetAttackDamage() << ")" << endl;
	hero.ShowAttacksInfo();
	this_thread::sleep_for(chrono::seconds(2));

	bool phase1Win = game.BossFight(hero, boss1, true); // lightning absorbed

	if (!phase1Win) {
		NarrateDefeat(game);
		return;
	}

	// Narrative: Evolution sequence
	NarrateEvolution(game, hero, weaponChoice);

	// Evolve hero attacks
	EvolveHeroAttacks(hero, weaponChoice);

	// Show new attacks
	cout << "Your evolved attacks:" << endl;
	cout << "1) Default attack (damage: " << hero.GetAttackDamage() << ")" << endl;
	hero.ShowAttacksInfo();
	this_thread::sleep_for(chrono::seconds(3));

	// Heal hero to 80% for Phase 2
	int healTo = (int)(hero.GetMaxHealth() * 0.8);
	hero.AssignPlayerHealth(healTo);
	hero.ClearStatusEffects();
	cout << "Your health has been restored to " << hero.GetHealth() << " HP." << endl;
	this_thread::sleep_for(chrono::seconds(2));

	// Phase 2: Fight the Voidstorm Unleashed
	Player boss2 = CreateVoidstormPhase2();

	game.SpaceMax();
	cout << "=== PHASE 2: VOIDSTORM UNLEASHED ===" << endl;
	cout << "Your evolved attacks bypass the Voidstorm's absorption!" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << endl;

	bool phase2Win = game.BossFight(hero, boss2, false); // lightning no longer absorbed

	if (phase2Win) {
		NarrateVictory(game, hero);
	}
	else {
		NarrateDefeat(game);
	}
}
