#define topicSize 21
#define choiceSize 31
#define passSize 501
#define quessSize 151

typedef char string30[choiceSize]; 
typedef char string20[topicSize];
typedef char string500[passSize]; 
typedef char string150[quessSize]; 

struct question{
    string20 topic; 
    int num; 
    string150 question; 
    string30 c1, c2, c3, answer;
};