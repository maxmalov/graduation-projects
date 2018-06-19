using System;

using ServerFramework.Tasks;
using ServerFramework.Messaging;
using ServerFramework.Tasks.Jobs;

using TestChat.Jobs;

namespace TestChat.Messages
{
    class SolveEquationMessage : Message
    {
        double a, b, c;
        public SolveEquationMessage(double _a, double _b, double _c)
            : base()
        {
            a = _a;
            b = _b;
            c = _c;
        }
        public override void Handle(object context)
        {
            Task task = (Task)context;
            task.Scheduller.Add( new SolveQuadEquationJob(task,a,b,c) );
        }
    }

    class FindStringMessage : Message
    {
        string fName, Find;
        public FindStringMessage(string _fName, string _Find)
            : base()
        {
            fName = _fName;
            Find = _Find;
        }
        public override void Handle(object context)
        {
            Task task = (Task)context;
            task.Scheduller.Add(new FindStringInFileJob(task,fName,Find));
        }
    }
}
