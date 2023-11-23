-- a. modify the type of a column;
-- modify shoes size from int to tiny int
--use Lab2_DB_Shoes;
CREATE OR ALTER PROCEDURE setShoeSizeToTinyInt 
AS
	ALTER TABLE Shoes 
		ALTER COLUMN size TINYINT
GO

-- reverse operation: modify player age from tiny int to int

CREATE OR ALTER PROCEDURE setShoeSizeToInt 
AS
	ALTER TABLE Shoes 
		ALTER COLUMN size INT
GO

-- b. add / remove a column;
-- add buyers name to Buyers

CREATE OR ALTER PROCEDURE addNametoBuyers 
AS
	ALTER TABLE Buyers 
		ADD buyers_name varchar(20)
GO

--remove buyers name to Buyers

CREATE OR ALTER PROCEDURE removeNametoBuyers 
AS
	ALTER TABLE Buyers 
		Drop column buyers_name
GO

-- c. add / remove a DEFAULT constraint;
-- add default balance to buyers 100(special offer for Christmas)

CREATE OR ALTER PROCEDURE addDefaultToBalanceBuyers 
AS
	ALTER TABLE Buyers
		ADD CONSTRAINT default_balance
			DEFAULT 100 FOR balance
GO

--remove
CREATE OR ALTER PROCEDURE removeDefaultToBalanceBuyers 
AS
	ALTER TABLE Buyers
		DROP CONSTRAINT default_balance
GO

-- g. create / drop a table.
-- create table Bags

CREATE OR ALTER PROCEDURE addTableBags
AS
	CREATE TABLE Bags (
		id INT NOT NULL,
		bags_name VARCHAR(50),
		cost INT,
		sellers_id INT
	)
GO

-- drop table Physiotherapist

CREATE OR ALTER PROCEDURE dropTableBags
AS
	DROP TABLE IF EXISTS Bags
GO

-- d. add / remove a primary key;
-- set id from Bags as primary key

CREATE OR ALTER PROCEDURE addPrimaryKeyBags
AS
	ALTER TABLE Bags
	ADD CONSTRAINT bags_id PRIMARY KEY(id)
GO


-- remove id primary key from Bags

CREATE OR ALTER PROCEDURE removePrimaryKeyBags
AS
	ALTER TABLE Bags
	DROP CONSTRAINT IF EXISTS bags_id
GO

-- e. add / remove a candidate key;
-- add candidate key to buyers

CREATE OR ALTER PROCEDURE addCandidateKeyToBuyers
AS
	ALTER TABLE Buyers
		ADD CONSTRAINT buyers_ck UNIQUE (birth_date, balance)
GO

-- remove candidate key from buyers

CREATE OR ALTER PROCEDURE removeCandidateKeyFromBuyers
AS
	ALTER TABLE Buyers
		DROP CONSTRAINT IF EXISTS buyers_ck
GO

-- f. add / remove a foreign key;
-- add seller_id from Bags as foreign key

CREATE OR ALTER PROCEDURE addForeignKey
AS
	ALTER TABLE Bags
		ADD CONSTRAINT fk_sellersId
			FOREIGN KEY(sellers_id) REFERENCES Sellers(sellers_id) ON DELETE CASCADE
GO

-- remove foreign key sellers_id from Bags

CREATE OR ALTER PROCEDURE removeForeignKey
AS
	ALTER TABLE Bags
		DROP CONSTRAINT IF EXISTS fk_sellersId
GO

-- versions table

CREATE TABLE versionsTable (
	version INT
)
/*
INSERT INTO versionsTable VALUES (1) --the initial version

CREATE TABLE proceduresTable (
	fromVersion INT,
	toVersion INT,
	PRIMARY KEY(fromVersion, toVersion),
	procedureName VARCHAR(100)
)

INSERT INTO proceduresTable
	(fromVersion, toVersion, procedureName)
VALUES
	(1, 2, 'setShoeSizeToTinyInt'),
	(2, 1, 'setShoeSizeToInt'),
	(2, 3, 'addNametoBuyers'),
	(3, 2, 'removeNametoBuyers'),
	(3, 4, 'addDefaultToBalanceBuyers'),
	(4, 3, 'removeDefaultToBalanceBuyers'),
	(4, 5, 'addTableBags'),
	(5, 4, 'dropTableBags'),
	(5, 6, 'addPrimaryKeyBags'),
	(6, 5, 'removePrimaryKeyBags'),
	(6, 7, 'addCandidateKeyToBuyers'),
	(7, 6, 'removeCandidateKeyToBuyers'),
	(7, 8, 'addForeignKey'),
	(8, 7, 'removeForeignKey');
*/
CREATE or alter PROCEDURE goToVersion(@newVersion INT) 
AS
	DECLARE @curr INT
	DECLARE @procedureName VARCHAR(100)
	SELECT @curr = version FROM versionsTable

	IF  @newVersion > (SELECT MAX(toVersion) FROM proceduresTable)
		RAISERROR ('Bad version', 10, 1)
	ELSE
	BEGIN
		IF @newVersion = @curr
			PRINT('Already on this version!');
		ELSE
		BEGIN
			IF @curr > @newVersion
			BEGIN
				WHILE @curr > @newVersion
				BEGIN
					SELECT @procedureName = procedureName FROM proceduresTable 
					WHERE fromVersion = @curr AND toVersion = @curr - 1
					PRINT('executing: ' + @procedureName);
					EXEC(@procedureName)
					SET @curr = @curr - 1
				END
			END

			IF @curr < @newVersion
			BEGIN
				WHILE @curr < @newVersion
					BEGIN
						SELECT @procedureName = procedureName FROM proceduresTable
						WHERE fromVersion = @curr AND toVersion = @curr + 1
						PRINT('executing: ' + @procedureName);
						EXEC (@procedureName)
						SET @curr = @curr + 1
					END
			END

			UPDATE versionsTable SET version = @newVersion
		END
	END
GO


EXEC goToVersion 1


SELECT * FROM proceduresTable;
SELECT * FROM versionsTable;
update versionsTable
set version=1
exec removeCandidateKeyFromBuyers;
exec removeDefaultToBalanceBuyers
exec removeForeignKey
exec removeNametoBuyers
exec removePrimaryKeyBags
exec dropTableBags
select * from Buyers
select * from Bags
update Buyers
set balance=200
where buyers_id=23