using System;

using ServerFramework.Tasks;
using ServerFramework.Messaging;

using TestChat.Jobs;
using TestChat.States;
using TestChat.Messages;

namespace TestChat
{
    class Program
    {
        static void Main(string[] args)
        {
            Task tE = new Task();
            Task tF = new Task();
            tE.Start();
            tF.Start();
            Message msgS;

            msgS = new SolveEquationMessage(1, 2, 1);
            tE.Write(msgS);
            msgS = new SolveEquationMessage(1, 1, 1);
            tE.Write(msgS);
            msgS = new SolveEquationMessage(1, 2, - 3);
            tE.Write(msgS);
            //msgS = new FindStringMessage("D:\\Программирование\\CSharp projects\\TestChat\\TestChat\\input.txt", "test");
            //tF.Write(msgS);
            msgS = new SolveEquationMessage(0, 2, -3);
            tE.Write(msgS);

        }
    }
}
