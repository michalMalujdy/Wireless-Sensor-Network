import { DataType } from './../enums/DataType';
import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Reading } from '../interfaces/resources/reading';
import { Observable } from 'rxjs/Observable';
import { environment } from '../../environments/environment';
import { ListResult } from './resources/list-result';

@Injectable()
export class ApiClientService {

  private readonly hostname = environment.general.api_hostname;

  constructor(private readonly http: HttpClient) {

  }

  public getReadings(from: Date, to: Date, dataType: DataType): Observable<ListResult<Reading>> {
    return this.http.get<ListResult<Reading>>(
      `${this.hostname}/api/SensorReadings?from=${from.toISOString()}&to=${to.toISOString()}&dataType=${dataType}`);
  }
}
