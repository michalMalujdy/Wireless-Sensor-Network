import { DataType } from './../../enums/DataType';

export class Reading {
    id: string;
    deviceId: number;
    value: number;
    dataType: DataType;
    date: Date;
}
