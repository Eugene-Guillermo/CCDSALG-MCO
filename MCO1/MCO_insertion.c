/*
    Name: Joolz Ryane C. Simbahon
    Section: S15
*/

/*
    This function sorts suffixes in lexiographic order, creating
    a suffix array.

    Parameters:
    nA
    [] - array of starting positions
    strA[A] - array of string suffixes
    nLen - length of array
*/
void insertionSort (int nA
[], string strA[], int nLen)
{
    int i = 0, j = 0;
    string strKey;
    int nKey;

    for(j = 2; j <= nLen; j++)
    {
        strcpy(strKey,strA[j]);
        nKey = nA
        [j];
        i = j - 1;
        while(i > 0 && strcmp(strA[i],strKey) == 1)
        {
            strcpy(strA[i + 1],strA[i]);
            nA
            [i + 1] = nA
            [i];
            i -= 1;
        }
        strcpy(strA[i + 1],strKey);
        nA
        [i + 1] = nKey;
    }
}
