    #include "testlib.h"
    using namespace std;

    constexpr int MAX_OUT = 1e5;

    int main(int argc, char* argv[]){
        registerTestlibCmd(argc, argv);

        int n = inf.readInt();
        long long m = inf.readLong();

        int judge_a1 = ans.readInt();

        vector<int> participant_ans(n);

        if(judge_a1 == -1){
            int participant_a1 = ouf.readInt(-1, MAX_OUT);
            if(participant_a1 == -1){
                quitif(!ouf.seekEof(), _pe, "Invalid output format");
                quitf(_ok, "Jury also says it is impossible.");
            }
            quitif(participant_a1 == 0, _pe, "Invalid output format");
            //If we reached here that means judge says it is impossible
            //but participant has outputted some answer. So we need to check their answer.
            participant_ans[0] = participant_a1;
        }

        
        int startInd = (judge_a1 == -1) ? 1 : 0;
        for (int i = startInd; i < n; i++)
        {
            participant_ans[i] = ouf.readInt(1, MAX_OUT, "a_i");
        }

        for (long long i = 0; i < m; i++)
        {
            int u = inf.readInt();
            int v = inf.readInt();

            if(participant_ans[u-1] % 2 == participant_ans[v-1] % 2){
                quitf(_wa, "Sum of a_%d and a_%d is even.", u, v);
            }
        }
        
        quitif(!ouf.seekEof(), _pe, "Invalid output format");

        if(judge_a1 == -1){
            //This means participant's answer was correct and the jury's answer was wrong.
            quitf(_fail, "CRITICAL: Participant's answer seems to be valid whereas the jury says impossible.");
        }
        quitf(_ok, "Correct answer.");
    }