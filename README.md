# SkyHighSpy-OOD
SkyHighSpy codebase edited to implement OOD. Now includes game object classes and hierachies 

The gameplay is exactly the same as the original SkyHighSpy game I made - found in the SkyHighSpy repository - but as the next step in my C++ learning journey I refactored that code to separate out the different game objects and their behaviours; Agent 8, gems, particles, asteroid pieces asteroids and meteors which are a child of asteroids. All of these classes are children of the game object class from the SWiCS tutorial I followed - the previous step in learning Object Orientated Design, found in the SWiCS-Class-Tutorial repo -, though I have edited the game object class so that it better fits my needs for this game.

![image](https://user-images.githubusercontent.com/92981170/140783807-530d0fce-2c8c-4ccb-b66e-e6eb6812f58b.png)


Using OOD for this game I've noticed a significant reduction in the number of lines of code needed to produce the same gameplay - e.g not having to create vectors of objects in order to update them. It's also meant moving away from the PlayBuffer structure and in some cases writing my own code to replace the functions I no longer had access to now that I wasn't including the #define PLAY_USING_GAMEOBJECT_MANAGER. 
