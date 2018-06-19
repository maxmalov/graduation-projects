using System;

using ServerFramework.Tasks;
using ServerFramework.Tasks.Jobs;


using TestChat.States;

namespace TestChat.Jobs
{
    class SolveQuadEquationJob : Job
    {
        ScheduleAction CurrentAction;

        public SolveQuadEquationJob(Task task, double _a, double _b, double _c)
        {
            CurrentAction = new GetParamsState(this,_a,_b,_c);
        }

        public override ScheduleAction next()
        {
            return CurrentAction;
        }

        public void SetAction(ScheduleAction sa)
        {
            CurrentAction = sa;
        }
    }

    class FindStringInFileJob : Job
    {
        ScheduleAction CurrentAction;
        public FindStringInFileJob(Task task, string _fName, string _Find)
        {
            CurrentAction = new GetSrcStrings(this, _fName, _Find);
        }
        public override ScheduleAction next()
        {
            return CurrentAction;
        }
        public void SetAction(ScheduleAction sa)
        {
            CurrentAction = sa;
        }
    }

}
