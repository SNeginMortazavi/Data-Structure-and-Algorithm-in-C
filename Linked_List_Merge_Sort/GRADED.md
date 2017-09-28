# Grading for prog-assignment-8-neginmortazavi
**Class:** 2017SPCS5002SV<br>
**Date:** 2017-04-18<br>
**Grader:** pgust

## Total: 46/50
## Comments

* mergeSortedLinkedLists() (-1)
  * NULL terminate last node in slow list
    * Otherwise, requires unnecessary traversal in mergeSortLinkedListTD()

* mergeSortLinkedListTD() (-1)
  * Calling getListSize() saves nothing because it required full list traversal.
    * All you care about is list empty or list size == 1
      * if (listHead == NULL || listHead->next == NULL) …
 
* mergeSortLinkedListBU() (-2)
  * NO comments describing how algorithm operates, as required by assignment
