use [Lab2_DB_Shoes]


DROP TABLE IF EXISTS Collaborations;
DROP TABLE IF EXISTS SneakerArtist;
DROP TABLE IF EXISTS Releases;


-- Ta(aid, a2, �) => aid = releases_id, a2 = cost
CREATE TABLE Releases(
	releases_id INT NOT NULL PRIMARY KEY,
	cost INT Unique NOT NULL,
	name VARCHAR(50) NOT NULL
);



--Tb(bid, b2, �) => bid = artists_id, b2 = sneakers_made
CREATE TABLE SneakerArtist(
	artists_id INT NOT NULL PRIMARY KEY,
	sneakers_made INT NOT NULL,
	name VARCHAR(50) NOT NULL
);


-- Tc(cid, aid, bid, �) => cid = jtrID, aid = releases_id, bid = artists_id
CREATE TABLE Collaborations(
	collabs_id INT NOT NULL PRIMARY KEY,
	releases_id INT NOT NULL REFERENCES Releases(releases_id) ON DELETE CASCADE ON UPDATE CASCADE,
	artists_id INT NOT NULL REFERENCES SneakerArtist(artists_id) ON DELETE CASCADE ON UPDATE CASCADE
);


-- insert random data in Ta

DROP PROCEDURE IF EXISTS insertIntoReleases;
GO

CREATE PROCEDURE insertIntoReleases (@rows INT) AS
BEGIN
	DECLARE @release INT = 1;
	DECLARE @cost INT = 1;
	DECLARE @name VARCHAR(50) = 'Default Name';

	WHILE @rows > 0
	BEGIN
		INSERT INTO Releases(releases_id,cost,name)
		VALUES (@release, @cost, @name);

		SET @release = @release + 1;
		SET @cost = @cost + 1;
		SET @rows = @rows - 1;
	END
	
END
GO


-- insert random data in Tb

DROP PROCEDURE IF EXISTS insertIntoArtists;
GO

CREATE PROCEDURE insertIntoArtists (@rows INT) AS
BEGIN
	DECLARE @artist INT = 1;
	DECLARE @sneakers INT = 1000;
	DECLARE @name VARCHAR(50) = 'Default Tournament';

	WHILE @rows > 0
	BEGIN
		INSERT INTO SneakerArtist(artists_id,sneakers_made , name)
		VALUES (@artist, @sneakers, @name);

		SET @artist = @artist + 1;
		SET @sneakers = @sneakers + 10;
		SET @rows = @rows - 1;
	END

END
GO


-- insert random data in Tc

DROP PROCEDURE IF EXISTS insertIntoCollaborations;
GO

CREATE PROCEDURE insertIntoCollaborations (@rows INT) AS
BEGIN
	DECLARE @releases INT = 1;
	DECLARE @artist INT = 1;
	DECLARE @collabs INT = 1;

	WHILE @rows > 0
	BEGIN
		INSERT INTO Collaborations(collabs_id, releases_id, artists_id)
		VALUES (@collabs, @releases, @artist);

		SET @collabs = @collabs + 1;
		SET @releases = @releases + 1;
		SET @artist = @artist + 1;
		SET @rows = @rows - 1;
	END

END
GO


-- populate the tables

DELETE FROM Collaborations;
DELETE FROM Releases;
DELETE FROM SneakerArtist;

EXEC insertIntoReleases 10000;
EXEC insertIntoArtists 10000;
EXEC insertIntoCollaborations 10000;


-----------------------------------------------------------------------------------------------
/*
a. Write queries on Ta such that their execution plans contain the following operators:

	- clustered index scan;
	- clustered index seek;
	- nonclustered index scan;
	- nonclustered index seek;
	- key lookup.
*/

EXEC sp_helpindex Releases;

-- PK: releases_id => automatically created clustered index
-- unique: rank => automatically created unclustered index

-- clustered index scan => touch every row in the table

SELECT * FROM Releases;

-- clustered index seek => returns a specific subset from the clustered index

SELECT * FROM Releases
WHERE releases_id < 1000;

-- nonclustered index scan => scan the entire nonclustered index

SELECT cost FROM Releases;

-- nonclustered index seek => returns a specific subset from the nonclustered index

SELECT cost FROM Releases
WHERE cost < 100;

-- key lookup => nonclustered index seek + additional data needed

SELECT name, cost FROM Releases
WHERE cost = 1234;


-----------------------------------------------------------------------------------------------
/*
b. Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan. 
Create a nonclustered index that can speed up the query. Examine the execution plan again.
*/

-- first it's a clustered index scan 
SELECT sneakers_made FROM SneakerArtist
WHERE sneakers_made = 1400;

DROP INDEX IF EXISTS SneakerArtistNonclustered ON SneakerArtist

CREATE NONCLUSTERED INDEX SneakerArtistNonclustered ON SneakerArtist(sneakers_made)

-- now we have a nonclustered index seek, which is more efficient
SELECT sneakers_made FROM SneakerArtist
WHERE sneakers_made = 1400;


-----------------------------------------------------------------------------------------------
/*
c. Create a view that joins at least 2 tables. Check whether existing indexes are helpful; 
if not, reassess existing indexes / examine the cardinality of the tables.
*/

DROP VIEW IF EXISTS view1;
GO

CREATE VIEW view1 AS
	SELECT C.collabs_id, C.artists_id, A.sneakers_made, A.name FROM Collaborations C
	INNER JOIN SneakerArtist A ON C.artists_id = A.artists_id
	WHERE A.sneakers_made > 1500;
GO

DECLARE @start1 DATETIME = GETDATE();
SELECT * FROM view1
DECLARE @end1 DATETIME = GETDATE();

PRINT 'WITHOUT INDEXES: start: ' + CONVERT(NVARCHAR(MAX), @start1) + ', end: ' + CONVERT(NVARCHAR(MAX), @end1) 
		+ ', total time: ' + CONVERT(NVARCHAR(MAX), DATEDIFF(millisecond, @start1, @end1)) + ' milliseconds';


DROP INDEX IF EXISTS Nonclustered1 ON SneakerArtist

CREATE NONCLUSTERED INDEX Nonclustered1 ON SneakerArtist(sneakers_made)

DROP INDEX IF EXISTS Nonclustered2 ON SneakerArtist

CREATE NONCLUSTERED INDEX Nonclustered2 ON SneakerArtist(name)


DROP VIEW IF EXISTS view2;
GO

CREATE VIEW view2 AS
	SELECT C.collabs_id, C.artists_id, A.sneakers_made, A.name FROM Collaborations C
	INNER JOIN SneakerArtist A ON C.artists_id = A.artists_id
	WHERE A.sneakers_made > 1500;
GO

DECLARE @start2 DATETIME = GETDATE();
SELECT * FROM view2
DECLARE @end2 DATETIME = GETDATE();

PRINT 'WITH INDEXES: start: ' + CONVERT(NVARCHAR(MAX), @start2) + ', end: ' + CONVERT(NVARCHAR(MAX), @end2) 
		+ ', total time: ' + CONVERT(NVARCHAR(MAX), DATEDIFF(millisecond, @start2, @end2)) + ' milliseconds';