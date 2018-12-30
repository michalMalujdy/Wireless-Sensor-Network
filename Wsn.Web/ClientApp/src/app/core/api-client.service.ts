import { DataType } from './../enums/DataType';
import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Reading } from '../interfaces/resources/reading';
import { Observable } from 'rxjs/Observable';
import { environment } from '../../environments/environment';

@Injectable()
export class ApiClientService {

  private readonly hostname = environment.general.api_hostname;

  constructor(private readonly http: HttpClient) {

  }

  public getReadings(from: Date, to: Date, dataType: DataType): Observable<Reading[]> {
    return this.http.get<Reading[]>(`${this.hostname}/api/Readings?from=${from.toISOString()}&to=${to.toISOString()}&dataType=${dataType}`);
  }
}
