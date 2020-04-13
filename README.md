# Files

## Project 1
**This indexes are implemented**
1. Primary index using the Book_ID (for Books datafile)
2. Primary index using the Author_ID (for Authors datafile)
3. Secondary index using Author_ID (for Books datafile) //Author_ID is sec. key in Books datafile
4. Secondary index using Name (for Authors datafile)

The user can write a query that contains fixed key words (formatted in red below)
Examples for queries that user can write
select all from Books where Author_ID = ’xxxx’  // this query will use sec. index to get results
select all from Authors where Author_ID = ’xxxx’ // this query will use primary. index to get results
select Book_Tile from Books where Book_ID = ’xxxx’ // this query will use sec. index to get results
select all from Books and Authors

## Project 2
**Problem 1**
  search data inside the data file using a primary index using the ID field
· Implement the primary index using binary search tree (AVL tree is recommended)
· Data file organization is (variable length record): length indicator records, delimited fields.

**Problem 2**
 search data inside the data file using the hashing technique.
· Address space N= 997.
· Bucket size =2.
· Hashing method: Use Chaining with separate overflow area technique to handle collision, The hash function is
the multiplication method
· Data file organization is: fixed record length (record fixed length is 110 chars), delimited fields
· You can use auxiliary data structures in RAM or not.

**Problem 3**
search inside the data file using the following
hashing technique:
· The primary Index is Hashed (index size N= 997)
· Bucket size =1.
· Data file organization is (variable length record): length indicator records, delimited fields.
· The hash function is the multiplication method

