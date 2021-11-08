# SkyHighSpy-OOD
SkyHighSpy codebase edited to implement OOD. Now includes game object classes and hierachies 

The gameplay is exactly the same as the original SkyHighSpy game I made - found in the SkyHighSpy repository - but as the next step in my C++ learning journey I refactored that code to separate out the different game objects and their behaviours; Agent 8, gems, particles, asteroid pieces asteroids and meteors which are a child of asteroids. All of these classes are children of the game object class from the SWiCS tutorial I followed - the previous step in learning Object Orientated Design, found in the SWiCS-Class-Tutorial repo -, though I have edited the game object class so that it better fits my needs for this game.

![image](https://user-images.githubusercontent.com/92981170/140783807-530d0fce-2c8c-4ccb-b66e-e6eb6812f58b.png)


Using OOD for this game I've noticed a significant reduction in the number of lines of code needed to produce the same gameplay - e.g not having to create vectors of objects in order to update them. It's also meant moving away from the PlayBuffer structure and in some cases writing my own code to replace the functions I no longer had access to now that I wasn't including the #define PLAY_USING_GAMEOBJECT_MANAGER. 

![image](https://user-images.githubusercontent.com/92981170/140784282-134133b5-d81d-453d-a2d7-d02f69ba6a5c.png)

By having Meteors as children of Asteroids, they were able to share the update function, as they did previously, but different spawn functions. I kept the Types enumerator in as this facilitates the finding of objects but now there is class specific behaviour the asteroid agent8 is currently attached to can share the asteroid update function - because it is of the asteroid class - but be distinguished from the other asteroids elsewhere in the code because it is of type OBJ_ATTACHED.

![image](https://user-images.githubusercontent.com/92981170/140786394-b5891e0d-c13a-4578-87dc-61add22f6f47.png)

When refactoring my code I was able to combine the ring and dust particle effects into one class. Since they has do little class specific behaviour - the original rings didn't have a spawn function like the other game objects - it would over complicate my code to make both into their own classes. Instead I have designed the constructors so that a variety of particle effects can be through just this one class. This was especially true of the ring and dust particle effects because both of their update functions involved changing their scale, if in different directions.
