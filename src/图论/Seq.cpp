/*
S starts at 0
go range from 1 to n
n <- length of string S
*/

void build()
{
    for (int i = 0; i < 26; i++)
        last[i] = -1;
    for (int i = n; i; i--)
    {
        for (int j = 0; j < 26; j++)
            go[i][j] = last[j];
        last[S[i - 1] - 'a'] = i;
    }
    int now1 = last[T[0] - 'a'];
    for (int i = 1; i < m; i++)
        if (~now1)
            now1 = go[now1][T[i] - 'a'];
        else
            break;
}