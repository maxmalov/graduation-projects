using System;
using System.IO;

using ServerFramework;
using ServerFramework.Tasks;
using ServerFramework.Tasks.Jobs;

using TestChat.Jobs;

namespace TestChat.States
{
    class GetParamsState : ScheduleAction
    {
        double _a, _b, _c;

        public GetParamsState(SolveQuadEquationJob job, double a, double b, double c)
            : base(job)
        {
            _a = a;
            _b = b;
            _c = c;
        }
                
        public override void Handle(JobScheduller scheduller)
        {
            if (_a == 0)
                ((SolveQuadEquationJob)Job).SetAction(new IncorrectInputState((SolveQuadEquationJob)Job));
            else
                ((SolveQuadEquationJob)Job).SetAction(new CountDiscriminantState((SolveQuadEquationJob)Job, this));
        }

        internal double a
        {
            get
            {
                return _a;
            }
        }
        internal double b
        {
            get
            {
                return _b;
            }
        }
        internal double c
        {
            get
            {
                return _c;
            }
        }
    }

    class IncorrectInputState : ScheduleAction
    {
        public IncorrectInputState(SolveQuadEquationJob job)
            : base(job)
        {
        }
        public override void Handle(JobScheduller scheduller)
        {
            Console.WriteLine("\n Eq: Incorrect parametres");
            ((SolveQuadEquationJob)Job).SetAction(new FinishScheduleAction(Job));
        }
    }

    class CountDiscriminantState : ScheduleAction
    {
        double _D, _a, _b;

        public CountDiscriminantState(SolveQuadEquationJob job, GetParamsState gps)
            : base(job)
        {
            _a = gps.a;
            _b = gps.b;
            _D = _b * _b - 4 * _a * gps.c;
        }

        public override void Handle(JobScheduller scheduller)
        {
            if (_D < 0)
                ((SolveQuadEquationJob)Job).SetAction(new EmptyAnswerState((SolveQuadEquationJob)Job));
            else ((SolveQuadEquationJob)Job).SetAction(new CountRootsState((SolveQuadEquationJob)Job, this));
        }

        public double D
        {
            get 
            {
                return _D;
            }
        }
        public double a
        {
            get
            {
                return _a;
            }
        }
        public double b
        {
            get
            {
                return _b;
            }
        }
    }

    class EmptyAnswerState : ScheduleAction
    {
        public EmptyAnswerState(SolveQuadEquationJob job)
            : base(job)
        { 
        }
        public override void Handle(JobScheduller scheduller)
        {
            Console.WriteLine("\n Eq: There is no answer");
            ((SolveQuadEquationJob)Job).SetAction(new FinishScheduleAction(Job));
        }
    }

    class CountRootsState : ScheduleAction
    {
        double _x1, _x2;

        public CountRootsState(SolveQuadEquationJob job, CountDiscriminantState cds)
            : base(job)
        {
            _x1 = (cds.b - Math.Sqrt(cds.D)) / (2 * cds.a);
            _x2 = (cds.b + Math.Sqrt(cds.D)) / (2 * cds.a);
        }

        public override void Handle(JobScheduller scheduller)
        {
            Console.Write("\n Eq: x1 = {0}", _x1);
            if(_x1!=_x2)
                Console.Write(", x2 = {0}", _x2);

            ((SolveQuadEquationJob)Job).SetAction(new FinishScheduleAction(Job));
        }
    }


    class GetSrcStrings : ScheduleAction
    {
        string fName, Find;
        public GetSrcStrings(FindStringInFileJob job, string _fName, string _Find)
            : base(job)
        {
            fName = _fName;
            Find = _Find;
        }

        public override void Handle(JobScheduller scheduller)
        {
            if(fName.Equals("\0") || Find.Equals("\0"))
                ((FindStringInFileJob)Job).SetAction(new IncorrectInputStrings((FindStringInFileJob)Job));
            else
                ((FindStringInFileJob)Job).SetAction(new FindFile((FindStringInFileJob)Job, fName, Find));
        }
    }

    class FindFile : ScheduleAction
    {
        string fName, Find;
        FileStream fin;
        public FindFile(FindStringInFileJob job, string _fName, string _Find)
            : base(job)
        {
            fName = _fName;
            Find = _Find;
        }

        public override void Handle(JobScheduller scheduller)
        {
            try
            {
                fin = new FileStream(fName, FileMode.Open, FileAccess.Read);
                ((FindStringInFileJob)Job).SetAction(new FindString((FindStringInFileJob)Job,fin,Find));
            }
            catch (FileNotFoundException)
            {
                ((FindStringInFileJob)Job).SetAction(new FileNotFound((FindStringInFileJob)Job));
            }

        }
    }

    class FindString : ScheduleAction
    {
        string Find;
        FileStream fin;
        StreamReader fstr_in;
        int ind;

        public FindString(FindStringInFileJob job, FileStream _fin, string _Find)
            : base(job)
        {
            fin = _fin;
            Find = _Find;
        }


        public override void Handle(JobScheduller scheduller)
        {
            string stmp;
            ind = 0;
            fstr_in = new StreamReader(fin);
            while ( (stmp = fstr_in.ReadLine()) != null)
            {
                if (stmp.IndexOf(Find) != -1)
                {
                    ((FindStringInFileJob)Job).SetAction(new StringFound((FindStringInFileJob)Job, ind));
                    return;
                }
                ++ind;
            }
            ((FindStringInFileJob)Job).SetAction(new StringNotFound((FindStringInFileJob)Job));
        }
    }

    class IncorrectInputStrings : ScheduleAction
    {
        public IncorrectInputStrings(FindStringInFileJob job)
            : base(job)
        {
        }
        public override void Handle(JobScheduller scheduller)
        {
            Console.WriteLine("\n File: Incorrect parametres");
            ((FindStringInFileJob)Job).SetAction(new FinishScheduleAction(Job));
        }
 
    }

    class FileNotFound : ScheduleAction
    {
        public FileNotFound(FindStringInFileJob job)
            :base(job)
        {
        }

        public override void  Handle(JobScheduller scheduller)
        {
            Console.WriteLine("\n File: There is no file");
            ((FindStringInFileJob)Job).SetAction(new FinishScheduleAction(Job)); 	        
        }
    }   

    class StringNotFound : ScheduleAction
    {
        public StringNotFound(FindStringInFileJob job)
            :base(job)
        {
        }

        public override void  Handle(JobScheduller scheduller)
        {
            Console.WriteLine("\n File: There is no string is the file");
            ((FindStringInFileJob)Job).SetAction(new FinishScheduleAction(Job)); 	        
        } 
    }

    class StringFound : ScheduleAction
    {
        int ind;
        public StringFound(FindStringInFileJob job, int _ind)
            : base(job)
        {
            ind = _ind;
        }
        public override void Handle(JobScheduller scheduller)
        {
            Console.WriteLine("\n File: First entry in {0}", ind);
            ((FindStringInFileJob)Job).SetAction(new FinishScheduleAction(Job));
        } 
    }

}

