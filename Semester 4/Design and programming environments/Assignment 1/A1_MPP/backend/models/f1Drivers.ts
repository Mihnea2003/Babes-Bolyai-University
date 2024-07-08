export class F1Driver {
    private _id: number;
    private _name: string;
    private _team: string;
    private _age: number;

    constructor(id: number, name: string, team: string, age: number) {
        this._id = id;
        this._name = name;
        this._team = team;
        this._age = age;
    }

    //getters
    get id(): number {
        return this._id;
    }
    get name(): string{
        return this._name;
    }
    get team(): string{
        return this._team;
    }
    get age(): number{
        return this._age;
    }

    //setters
    set id(id: number){
        this._id = id;
    }
    set name(name: string){
        this._name = name;
    }
    set team(team: string){
        this._team = team;
    }
    set age(age: number){
        this._age = age;
    }

    //toString
    public toString = (): string =>{
        return 'F1 Driver: ' + this._name + ' Team: ' + this._team + ' Age: ' + this._age +'\n';
    }
}