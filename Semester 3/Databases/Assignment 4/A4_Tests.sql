use [Lab2_DB_Shoes]

--------------------- insert into tables ---------------------

DROP PROCEDURE IF EXISTS insertIntoTables;
GO

CREATE PROCEDURE insertIntoTables (@tableName VARCHAR(60)) AS
BEGIN
	IF @tableName IN (SELECT Name FROM Tables)
	BEGIN
		PRINT 'Table already in Tables!'
		RETURN
	END

	INSERT INTO Tables (Name)
	VALUES (@tableName);
END
GO


--------------------- insert into views ---------------------

DROP PROCEDURE IF EXISTS insertIntoViews;
GO

CREATE PROCEDURE insertIntoViews (@viewName VARCHAR(70)) AS
BEGIN
	IF @viewName IN (SELECT Name FROM Views)
	BEGIN
		PRINT 'View already in Views!'
		RETURN
	END

	INSERT INTO Views (Name)
	VALUES (@viewName)

END
GO

--------------------- insert into tests ---------------------

DROP PROCEDURE IF EXISTS insertIntoTests;
GO

CREATE PROCEDURE insertIntoTests (@testName VARCHAR(70), @testID INT) AS
BEGIN
	IF @testName IN (SELECT Name FROM Tests)
	BEGIN
		PRINT 'Test already in Tests!'
		RETURN
	END

	INSERT INTO Tests (Name)
	VALUES (@testName)
END
GO

--------------------- connect table to test ---------------------

DROP PROCEDURE IF EXISTS connectTableToTest;
GO

CREATE PROCEDURE connectTableToTest (@tableName VARCHAR(70), @testName VARCHAR(70), @nb_of_rows INT, @position INT) AS
BEGIN
	INSERT INTO TestTables (TestID, TableID, NoOfRows, Position)
	VALUES (
		(SELECT TestID FROM Tests WHERE Name = @testName),
		(SELECT TableID FROM Tables WHERE Name = @tableName),
		@nb_of_rows,
		@position
	)

END
GO
	


--------------------- connect view to test ---------------------

DROP PROCEDURE IF EXISTS connectViewToTest;
GO

CREATE PROCEDURE connectViewToTest (@viewName VARCHAR(70), @testName VARCHAR(70)) AS
BEGIN
	INSERT INTO TestViews (TestID, ViewID)
	VALUES (
		(SELECT TestID FROM Tests WHERE Name = @testName),
		(SELECT ViewID FROM Views WHERE Name = @viewName)
	)
END
GO


--------------------- generate random string ---------------------

DROP PROCEDURE IF EXISTS generateRandomString;
GO

CREATE PROCEDURE generateRandomString (@string VARCHAR(21) OUTPUT) AS
BEGIN
	DECLARE @counter INT = 0;
	DECLARE @limit INT = 5 + RAND() * 20;

	SET @string = '';

	WHILE (@counter < @limit)
	BEGIN
		SET @string = @string + CHAR((RAND() * 25 + 97));
		SET @counter = @counter + 1;
	END
END
GO

--------------------- generate random int ---------------------

DROP PROCEDURE IF EXISTS generateRandomInt;
GO

CREATE PROCEDURE generateRandomInt (@lowLimit INT, @maxLimit INT, @integer INT OUTPUT) AS
BEGIN
	SET @integer = @lowLimit + RAND() * @maxLimit;
END
GO


--------------------- foreign keys retrieval ---------------------

DROP PROCEDURE IF EXISTS getReferenceData;
GO

CREATE PROCEDURE getReferenceData (@table VARCHAR(128), @column VARCHAR(128), @referencedTable VARCHAR(128) OUTPUT, @referencedColumn VARCHAR(128) OUTPUT)
AS
BEGIN
	SELECT @referencedTable = OBJECT_NAME(FC.referenced_object_id), @referencedColumn = COL_NAME(FC.referenced_object_id, FC.referenced_column_id)
	FROM sys.foreign_keys AS F INNER JOIN sys.foreign_key_columns AS FC ON F.OBJECT_ID = FC.constraint_object_id
	WHERE OBJECT_NAME (F.parent_object_id) = @table AND COL_NAME(FC.parent_object_id, FC.parent_column_id) = @column
END
GO


--------------------- primary key retrieval ---------------------

DROP FUNCTION IF EXISTS isPrimaryKey;
GO

CREATE FUNCTION isPrimaryKey (@table VARCHAR(128), @column VARCHAR(128))
RETURNS INT
AS
BEGIN
	DECLARE @counter INT = 0
	SET @counter = (
		SELECT count(*)
		FROM     INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS C
			JOIN INFORMATION_SCHEMA.KEY_COLUMN_USAGE  AS K ON C.TABLE_NAME = K.TABLE_NAME
																 AND C.CONSTRAINT_CATALOG = K.CONSTRAINT_CATALOG
																 AND C.CONSTRAINT_SCHEMA = K.CONSTRAINT_SCHEMA
																 AND C.CONSTRAINT_NAME = K.CONSTRAINT_NAME
		WHERE   C.CONSTRAINT_TYPE = 'PRIMARY KEY'
				AND K.COLUMN_NAME = @column
				AND C.TABLE_NAME = @table
		)

	IF @counter = 0 BEGIN
		RETURN 0
	END

	RETURN 1
END
GO

--------------------- insert a row of data in a given table ---------------------

DROP PROCEDURE IF EXISTS insertRow;
GO

CREATE PROCEDURE insertRow (@tableName VARCHAR(70)) AS
BEGIN
	DECLARE @getColumnsQuery NVARCHAR(MAX) = N' 
		SELECT COLUMN_NAME, DATA_TYPE
		FROM INFORMATION_SCHEMA.COLUMNS
		WHERE TABLE_NAME = ''' + @tableName + '''
	';

	DECLARE @insertQuery NVARCHAR(MAX) = N'INSERT INTO ' + @tableName;

	DECLARE @columns NVARCHAR(MAX);
	DECLARE @types NVARCHAR(MAX);
	DECLARE @rowsNumber INT = 0;

	-- we use a cursor to extract all columns from the table and their types
	DECLARE @cursorQuery NVARCHAR(MAX) = N'
		DECLARE @columnName NVARCHAR(MAX);
		DECLARE @dataType NVARCHAR(MAX);
		DECLARE columnsCursor CURSOR FOR ' + @getColumnsQuery + '
		OPEN columnsCursor
		FETCH columnsCursor
		INTO @columnName, @dataType;

		IF @@FETCH_STATUS = 0
		BEGIN
			SET @columns = @columnName;
			SET @types = @dataType;
			SET @rowsNumber = 1;
		END

		WHILE @@FETCH_STATUS = 0
		BEGIN
			FETCH columnsCursor
			INTO @columnName, @dataType;
			IF @@FETCH_STATUS = 0
			BEGIN
				SET @columns = @columns + '', '' + @columnName;
				SET @types = @types + '', '' + @dataType;
				SET @rowsNumber = @rowsNumber + 1;
			END
		END

		CLOSE columnsCursor;
		DEALLOCATE columnsCursor;	
	';

	EXEC sp_executesql @Query = @cursorQuery, @Params = N'@columns NVARCHAR(MAX) OUTPUT, @types NVARCHAR(MAX) OUTPUT, @rowsNumber INT OUTPUT', @columns = @columns OUTPUT, @types = @types OUTPUT, @rowsNumber = @rowsNumber OUTPUT;

	SET @insertQuery = @insertQuery + '(' + @columns + ') VALUES (';

	SET @types = @types + ', ';
	SET @columns = @columns + ', ';

	DECLARE @index INT = 0;
	DECLARE @current NVARCHAR(MAX);
	DECLARE @currentColumn NVARCHAR(MAX);
	DECLARE @pkConstraint INT = 0;
	DECLARE @outputPK INT;
	DECLARE @pkQuery NVARCHAR(MAX)

	-- now we insert random data on every column
	WHILE @index < @rowsNumber
	BEGIN
		SET @current = LEFT(@types, CHARINDEX(', ', @types) - 1);
		SET @types = SUBSTRING(@types, CHARINDEX(', ', @types) + 2, LEN(@types));
		SET @currentColumn = LEFT(@columns, CHARINDEX(', ', @columns) - 1);
		SET @columns = SUBSTRING(@columns, CHARINDEX(', ', @columns) + 2, LEN(@columns));

		IF @index != 0
			SET @insertQuery = @insertQuery + ', ';

		DECLARE @referencedTable NVARCHAR(MAX) = '';
		DECLARE @referencedColumn NVARCHAR(MAX) = '';
		
		-- here we check if the current column has a foreign key 
		EXEC getReferenceData @tableName, @currentColumn, @referencedTable = @referencedTable OUTPUT, @referencedColumn = @referencedColumn OUTPUT;
	
		-- here we check if the current column has a primary key
		SET @pkConstraint = dbo.isPrimaryKey(@tableName, @currentColumn);
		--PRINT @pkConstraint;

		-- case 1: we must insert a integer
		IF @current = 'INT'
		BEGIN
			-- case 1.1: it's a foreign key => we must search in the refferenced table
			IF @referencedTable != '' AND @referencedColumn != ''
			BEGIN
				DECLARE @intValue INT;
				DECLARE @intQuery NVARCHAR(MAX) = N'
					SELECT @intValue = ' + @referencedColumn + ' FROM ' + @referencedTable;
				--PRINT @intQuery
				EXEC sp_executesql @Query = @intQuery, @Params = N'@intValue INT OUTPUT', @intValue = @intValue OUTPUT;
				SET @insertQuery = @insertQuery + CONVERT(NVARCHAR(MAX), @intValue);
			END
			ELSE
			BEGIN
				DECLARE @integer INT;
				-- case 1.2: it's a primary key => we generate a random value and we must check if the value doesn't already exist
				IF @pkConstraint = 1
				BEGIN
					EXEC generateRandomInt 0, 1000, @integer = @integer OUTPUT;
					SET @pkQuery = N'SELECT @outputPK = COUNT (*) FROM ' + @tableName + ' WHERE '	+ @currentColumn + '=' + CONVERT(NVARCHAR(MAX), @integer);
					EXEC sp_executesql @pkQuery, N'@outputPK INT OUTPUT', @outputPK OUTPUT
					PRINT @outputPK
					IF @outputPK != NULL
					BEGIN
						WHILE @outputPK != NULL 
						BEGIN
							SET @pkQuery = N'SELECT @outputPK = COUNT (*) FROM ' + @tableName + ' WHERE '	+ @currentColumn + '=' + CONVERT(NVARCHAR(MAX), @integer);
							EXEC sp_executesql @pkQuery, N'@outputPK INT OUTPUT', @outputPK OUTPUT
						END
					END
					SET @insertQuery = @insertQuery + CONVERT(NVARCHAR(MAX), @integer);
				END
				-- case 1.3: it's not a foreign key or a primary key => we insert a random value
				ELSE
				BEGIN
					EXEC generateRandomInt 0, 1000, @integer = @integer OUTPUT;
					SET @insertQuery = @insertQuery + CONVERT(NVARCHAR(MAX), @integer);
				END

			END
		END

		-- case 2: we must insert a string
		IF @current = 'VARCHAR'
		BEGIN
			-- case 2.1: it's a foreign key => we must search in the refferenced table
			IF @referencedTable != '' AND @referencedColumn != ''
			BEGIN
				DECLARE @stringValue NVARCHAR(MAX);
				DECLARE @stringQuery NVARCHAR(MAX) = N'
					SELECT @stringValue = ' + @referencedColumn + ' FROM ' + @referencedTable;
				EXEC sp_executesql @Query = @stringQuery, @Params = N'@stringValue INT OUTPUT', @stringValue = @stringValue OUTPUT;
				SET @insertQuery = @insertQuery + CONVERT(NVARCHAR(MAX), @stringValue);
			END
			ELSE 
			BEGIN
				DECLARE @string NVARCHAR(21);
				-- case 2.2: it's a primary key => we generate a random value and we must check if the value doesn't already exist
				IF @pkConstraint = 1
				BEGIN
					EXEC generateRandomString @string = @string OUTPUT;
					SET @pkQuery = N'SELECT @outputPK = COUNT (*) FROM ' + @tableName + ' WHERE '	+ @currentColumn + '=' + @string;
					EXEC sp_executesql @pkQuery, N'@outputPK VARCHAR OUTPUT', @outputPK OUTPUT;
					PRINT @outputPK;
					IF @outputPK != NULL
					BEGIN
						WHILE @outputPK != NULL 
						BEGIN
							SET @pkQuery = N'SELECT @outputPK = COUNT (*) FROM ' + @tableName + ' WHERE '	+ @currentColumn + '=' + @string;
							EXEC sp_executesql @pkQuery, N'@outputPK VARCHAR OUTPUT', @outputPK OUTPUT;
						END
					END
					SET @insertQuery = @insertQuery + '''' + @string + '''';
				END
				-- case 2.3: it's not a foreign key or a primary key => we insert a random value
				ELSE
				BEGIN
					EXEC generateRandomString @string = @string OUTPUT;
					SET @insertQuery = @insertQuery + '''' + @string + '''';
				END
			END
		END

		SET @index = @index + 1;
	END

	SET @insertQuery = @insertQuery + ');';
	PRINT @insertQuery;
	EXEC sp_executesql @insertQuery;
END
GO


--------------------- insert multiple rows of data in a given table ---------------------

DROP PROCEDURE IF EXISTS insertMultipleRows;
GO

CREATE PROCEDURE insertMultipleRows (@tableName VARCHAR(70), @nb INT) AS
BEGIN
	WHILE @nb > 0
	BEGIN
		DECLARE @error INT = 1;
		WHILE @error != 0
		BEGIN
			SET @error = 0;
			BEGIN TRY
				EXEC insertRow @tableName;
			END TRY
			BEGIN CATCH
				SET @error = 1;
			END CATCH
		END

		SET @nb = @nb - 1;
	END
END 
GO


--------------------- run test procedure ---------------------

DROP PROCEDURE IF EXISTS runTest;
GO

CREATE PROCEDURE runTest (@testID INT) AS
BEGIN
	DECLARE @tests INT = 0;
	DECLARE @tableID INT = -1;
	DECLARE @viewID INT = -1;
	DECLARE @rowsNb INT = -1;
	DECLARE @runID INT = -1;
	DECLARE @testStart DATETIME = GETDATE();

	INSERT INTO TestRuns (Description, StartAt)
	VALUES ((SELECT Name FROM Tests WHERE TestID = @testID), @testStart);

	SELECT @runID = TestRunID FROM TestRuns 
	WHERE Description = (SELECT Name FROM Tests WHERE TestID = @testID) AND StartAt = @testStart;

	SELECT @tests = COUNT(*) FROM Tests
	WHERE TestID = @testID;

	IF @testID < 0
	BEGIN
		RAISERROR('Invalid test ID!', 10, 1);
		RETURN
	END

	-- run test for tables --

	DECLARE @tableName NVARCHAR(MAX);
	DECLARE @query NVARCHAR(MAX);

	-- first we delete data from the tables --

	DECLARE testCursor CURSOR FOR
	SELECT TableID FROM TestTables
	WHERE TestID = @testID
	ORDER BY Position DESC;

	OPEN testCursor
	FETCH testCursor
	INTO @tableId;

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SELECT @tableName = Name FROM Tables
		WHERE TableID = @tableID;

		SET @query = N'DELETE FROM ' + @tableName;
		EXEC sp_executesql @query;

		FETCH testCursor
		INTO @tableId;
	END

	CLOSE testCursor
	DEALLOCATE testCursor

	-- now we insert data to tables --
	
	DECLARE testCursor CURSOR FOR
	SELECT TableID, NoOfRows FROM TestTables
	WHERE TestID = @testID
	ORDER BY Position;

	OPEN testCursor
	FETCH testCursor
	INTO @tableId, @rowsNb;

	DECLARE @startInsert DATETIME;
	DECLARE @endInsert DATETIME;

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SELECT @tableName = Name FROM Tables
		WHERE TableID = @tableID;

		SET @startInsert = GETDATE();
		EXEC insertMultipleRows @tableName, @rowsNb;
		SET @endInsert = GETDATE();

		INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
		VALUES (@runID, @tableID, @startInsert, @endInsert)

		FETCH testCursor
		INTO @tableID, @rowsNb;
	END

	CLOSE testCursor
	DEALLOCATE testCursor

	-- run test for views --

	DECLARE @viewName NVARCHAR(MAX);

	DECLARE testCursor CURSOR FOR
	SELECT ViewID FROM TestViews
	WHERE TestID = @testID

	OPEN testCursor
	FETCH testCursor 
	INTO @viewID;

	DECLARE @startView DATETIME;
	DECLARE @endView DATETIME;

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SELECT @viewName = Name FROM Views
		WHERE ViewID = @viewID;

		SET @query = 'SELECT * FROM ' + @viewName;

		SET @startView = GETDATE();
		EXEC sp_executesql @query;
		SET @endView = GETDATE();

		INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt)
		VALUES (@runID, @viewID, @startView, @endView);

		FETCH testCursor
		INTO @viewID;
	END

	CLOSE testCursor;
	DEALLOCATE testCursor;

	-- set TestRuns table data --
	UPDATE TestRuns
	SET EndAt = GETDATE()
	WHERE Description = (SELECT Name FROM Tests WHERE TestID = @testID) AND StartAt = @testStart;

END 
GO


--------------------- views ---------------------

-- a view with a SELECT statement operating on one table

CREATE OR ALTER VIEW SellersMoneyView
AS 
	SELECT * FROM Sellers2
	WHERE bank_account>500;
GO

-- a view with a SELECT statement that operates on at least 2 different tables and contains at least one JOIN operator
CREATE OR ALTER VIEW SellersobjectsView
AS
	SELECT SH.* FROM Shops2 SH
	LEFT JOIN Sellers2 S ON Sh.shops_id = S.shops_id
	LEFT JOIN Bosses2 B ON B.shops_id = SH.shops_id
GO


-- a view with a SELECT statement that has a GROUP BY clause, operates on at least 2 different tables and contains at least 
-- one JOIN operator

CREATE OR ALTER VIEW BuyersView
AS
	SELECT B.buyers2_name, S.sellers_name
	FROM Buyers2 B
	INNER JOIN Sellers2 S ON S.sellers_id = B.sellers_id
	GROUP BY B.buyers2_name, S.sellers_name;
GO


--------------------- create the tests ---------------------

--------------------- TEST 1 ---------------------
-- a table with a single-column primary key and at least one foreign key : Sellers

EXEC insertIntoViews 'SellersMoneyView'
EXEC insertIntoTests 'test1', 1
EXEC insertIntoTables 'Sellers2'
EXEC connectTableToTest 'Sellers2', 'test1', 500, 1
EXEC connectViewToTest 'SellersMoneyView', 'test1'


--------------------- TEST 2 ---------------------
-- a table with a single-column primary key and no foreign keys : Shops

EXEC insertIntoViews 'SellersobjectsView'
EXEC insertIntoTests 'test2', 2
EXEC insertIntoTables 'Shops2'
EXEC connectTableToTest 'Shops2', 'test2', 500, 1
EXEC insertIntoTables 'Sellers2'
EXEC connectTableToTest 'Sellers2', 'test2', 500, 2
EXEC insertIntoTables 'Bosses2'
EXEC connectTableToTest 'Bosses2', 'test2', 500,3
EXEC connectViewToTest 'SellersobjectsView', 'test2'


--------------------- TEST 3 ---------------------
-- a table with a multicolumn primary key 

EXEC insertIntoViews 'BuyersView'
EXEC insertIntoTests 'test3', 3
EXEC insertIntoTables 'Sellers2'
EXEC connectTableToTest 'Sellers2', 'test3', 500, 1
EXEC insertIntoTables 'Buyers2'
EXEC connectTableToTest 'Buyers2', 'test3', 500, 2
EXEC connectViewToTest 'BuyersView', 'test3'

INSERT INTO Shops2 (shops_id, location, workers)
VALUES (1, 'Bucuresti', 10),
       (2, 'Cluj-Napoca', 8),
       (3, 'Iasi', 6);

INSERT INTO Sellers2 (sellers_id, sellers_name, bank_account, shops_id)
VALUES (1, 'John', 12345, 1),
       (2, 'Maria', 67890, 2),
       (3, 'Alex', 24680, 3);

INSERT INTO Bosses2(bosses_id, bosses_name, bank_account, shops_id) VALUES (1, 'Boss 1', 99999, 1);
INSERT INTO Bosses2(bosses_id, bosses_name, bank_account, shops_id) VALUES (2, 'Boss 2', 88888, 2);

INSERT INTO Buyers2 (buyers2_id, buyers2_name, money, sellers_id)
VALUES (1, 'John Doe', 100, 3);
SELECT * FROM Sellers2;
SELECT * FROM Buyers;
SELECT * FROM Bosses2;
Select * FROM Shops2;

DELETE FROM Sellers2;
DELETE FROM Shops2;
DELETE FROM Buyers;
DELETE FROM Bosses2;

SELECT * FROM Tests
SELECT * FROM Tables
SELECT * FROM Views
SELECT * FROM TestTables
SELECT * FROM TestViews
SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews
EXEC runTest 2;
delete FROM Tests
delete FROM Tables
delete FROM Views
delete FROM TestTables
delete FROM TestViews
delete FROM TestRuns
delete FROM TestRunTables
delete FROM TestRunViews

Drop table TestRunViews;
drop table TestRunTables;
drop table TestRuns;
drop table TestViews;
drop table TestTables;
drop table Views;
drop table Tables;
drop table Tests;