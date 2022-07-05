# Alex's RPG Simulation Battle Game
### The idea of the game is for the two entities to fight each other using the simulate() function. Two entities will then fight a specified number of times and then the results of the fights will be printed. The winner is the entity who wins the majority of the simulated fights.
#### You can create your own entity using createPlayer() and allocate MAX_POINTS points to upgrade the player's health, attack, or defense or just use the createEntity() directly to skip the dialogue.
##### TODO:
Add different types of entities with unique abilities.

Implement simple "AI" to decide if the entity should attack, sit back and heal, or use their ability.

Balance all of this :( (By far the most annoying part of creating this game, attack points are OP rn)

Implement upgrade player and add bosses to simulate fights against.

Possibly add a mode that instead of simulating, the player can actually play against the AI for 1 battle and win or lose.

#### Why:
I finally finished up all my reading about the more advanced C++ topics such as inheritance, virtual functions, exceptions, templates, smart pointers and move semantics, and I started messing around with all of them one day. That day I had created a messy and horrible version of this game.

One of the major problems with that first edition was my random number generation. In my first commit, I tried a bunch of random number generators that I either thought of and wrote or found online. I didn't know how good these generators were, so I wrote two algorithms to test their performance. In the rng.cpp, I tested a bunch of different rng() functions, looked and their duplicate values per 1 million numbers generated, and the distribution of these numbers. The current rng() performs really well and gave me a basis to start the rng aspect of this game.
