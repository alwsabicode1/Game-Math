#include <iostream>
using namespace std;
enum enQuestionLevel
{
    Easy = 1, Mid = 2, Hard = 3, Mix = 4

};
enum enOperationType
{
    Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5

};
struct stQuestion
{
    int Num1 = 0;
    int Num2 = 0;
    enQuestionLevel QuestionLevel;
    enOperationType OperationType;
    int CorrectAnswer=0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;


};
struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestion;
    enQuestionLevel QuestonLevel;
    enOperationType OpType;
    short NumberOfRight = 0;
    short NumberOfWrong = 0;
    bool isPass = false;

};
int RandomNumber(int From, int To) {
    int random = rand() % (To - From + 1) + From;
    return random;
}
short ReadHowManyQuestion() {
    short NumberOfQuestion;
    do
    {
        cout << "How Many Questions Do You Want Answer?";
        cin >> NumberOfQuestion;

    } while (NumberOfQuestion<1||NumberOfQuestion>20);
    return NumberOfQuestion;
}
enQuestionLevel ReadQuestionLevel() {
    short QuestionLevel=0;
    do
    {
        cout << "Enter Question Level  [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ";
        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel>4);
    return (enQuestionLevel)QuestionLevel;
}
enOperationType ReadOpType() {
    short OpType ;
    do
    {
        cout << "Enter Operation Type  [1]:Add, [2]:Sub, [3]:Mult, [4]:Div, [5]:Mix ? ";
        cin >> OpType;

    } while (OpType < 1 || OpType>5);
    return (enOperationType)OpType;
}
enOperationType GetRandomOperationType() {
    int Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}
int SimpleCalculator(int num1, int num2, enOperationType OpType) {
    switch (OpType)
    {
    case enOperationType::Add:
        return num1 + num2;
    case enOperationType::Sub:
        return num1 - num2;
    case enOperationType::Mult:
        return num1 * num2;
    case enOperationType::Div:
        return num1 / num2;
    default:
        return num1 + num2;

    }
}
string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "x";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType) {
    stQuestion Question;
    if (QuestionLevel == enQuestionLevel::Mix) {
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    }
    if (OpType == enOperationType::MixOp) {
        OpType = GetRandomOperationType();
    }
    Question.OperationType = OpType;
    switch (QuestionLevel)
    {
    case enQuestionLevel::Easy:
        Question.Num1 = RandomNumber(1, 10);
        Question.Num2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Num1, Question.Num2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::Mid:
        Question.Num1 = RandomNumber(1, 50);
        Question.Num2 = RandomNumber(1, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Num1, Question.Num2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::Hard:
        Question.Num1 = RandomNumber(50, 100);
        Question.Num2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Num1, Question.Num2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    }
}
void GenerateQuizzQuestion(stQuizz& Quizz) {
    for (short i = 0; i < Quizz.NumberOfQuestion; i++)
    {
        Quizz.QuestionList[i] = GenerateQuestion(Quizz.QuestonLevel, Quizz.OpType);

    }
}
int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}
void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" <<
        Quizz.NumberOfQuestion << "] \n\n";
    cout << Quizz.QuestionList[QuestionNumber].Num1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Num2 << " ";
    cout <<
        GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n_________" << endl;
}
void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); //turn screen to Green
    else
    {
        system("color 4F"); //turn screen to Red
        cout << "\a";
    }
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short
    QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer !=
        Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrong++;
        cout << "Worng Answer :-( \n";
        cout << "The right answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRight++;
        cout << "Right Answer :-) \n";
    }
    cout << endl;
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz) {
    for (short i = 0; i < Quizz.NumberOfQuestion; i++)
    {
        PrintTheQuestion(Quizz, i);
        Quizz.QuestionList[i].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz,i);

    }
    Quizz.isPass = (Quizz.NumberOfRight >= Quizz.NumberOfWrong);
}
string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "PASS :-)";
    else
        return "Fail :-(";
}
string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix"};
    return arrQuestionLevelText[QuestionLevel - 1];
}
void PrintQuizzResult(stQuizz Quizz)
{
    cout << "\n";
    cout << "______________________________\n\n";
    cout << " Final Resutls is " <<
        GetFinalResultsText(Quizz.isPass);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions: " << Quizz.NumberOfQuestion <<
        endl;
    cout << "Questions Level : " <<
        GetQuestionLevelText(Quizz.QuestonLevel) << endl;
    cout << "OpType : " <<
        GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right Answers: " <<
        Quizz.NumberOfRight << endl;
    cout << "Number of Wrong Answers: " <<
        Quizz.NumberOfWrong << endl;
    cout << "______________________________\n";
}
void  PlayMath() {
    stQuizz Quizz;
    Quizz.NumberOfQuestion = ReadHowManyQuestion();
    Quizz.QuestonLevel = ReadQuestionLevel();
    Quizz.OpType = ReadOpType();
    GenerateQuizzQuestion(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResult(Quizz);
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
void StartGame() {
    char PlayAgin = 'Y';
    do
    {
        ResetScreen();
        PlayMath();
        cout << "Do You Want To Play Again ! Yes/No ?";
        cin >> PlayAgin;


    } while (PlayAgin=='Y' || PlayAgin == 'y');
}
int main()
{
    StartGame();
    
}

