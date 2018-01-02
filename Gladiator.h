#ifndef MIVNE1_GLADIATOR_H
#define MIVNE1_GLADIATOR_H

class Gladiator
{
private:
    int ID;
    int level;
    Trainer * pTrainer;

public:
    Gladiator();

    Gladiator(int ID, int level, Trainer* trainer);

    Gladiator(const Gladiator&);

    Gladiator& operator=(const Gladiator& glad){
		if (this == &glad) {
		 return *this;
		}
		ID = glad.ID;
		level = glad.level;
		pTrainer = glad.pTrainer;
		return *this;
	}

    void SetID(int ID);

    void SetLevel(int level);

    void SetTrainer( Trainer* trainer);

    int getID(){
    	return ID;
    }

    int getLevel(){
    	return level;
    }

    Trainer* getPTrainer(){
    	return pTrainer;
    }

};

class CompareGladiatorID {
public:
    int operator() (Gladiator g1, Gladiator g2){
        return (g1.getID() - g2.getID());
    }
};


class CompareGladiatorLevel{
public:
	int operator() (Gladiator glad1, Gladiator glad2){
		if(glad1.getLevel() != glad2.getLevel()){
			return (glad1.getLevel()-glad2.getLevel());
		}
		return (glad2.getID()-glad1.getID());
	}
};


#endif //MIVNE1_GLADIATOR_H
