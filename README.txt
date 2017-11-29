Relational Data Model

This Project was done by Abdullah Alsayari and Islomzhan Akhmedov

Part1:1. We created different structs for different relations or tables2. We used “*” to represent any attributes that are not specified.3. We used file write and read functions:
	* That saves the database by func saveDatabase();
	* And loads the database by func loadDatabase();
4. displayRelations() - lists the tuples on appropriate buckets of Hashtable
5. there’re some other functions like lookup, insert, delete that we wrote
Part2:1. We created a tree of pointers where the name is the domain for the secondary indexrelation, to tuples as a secondary index base structure for each relations using Binary Search Tree.
Part3:1. We created a general data base to be able to merge two relations in case of join.2. We made unfinished implementations for “select”, “projection”, and “join”.

HOW TO RUN:
type “make” to build the project
type “./SNAPtest”, “./CDHtest”, “./CSGtest”, “./CRtest”, “./CPtest”, “./QUERYtest”
to test these above files. 