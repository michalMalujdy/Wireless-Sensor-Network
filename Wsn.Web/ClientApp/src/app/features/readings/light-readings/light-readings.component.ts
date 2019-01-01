import { environment } from './../../../../environments/environment';
import { Component, OnInit } from '@angular/core';
import { HubConnection, HubConnectionBuilder } from '@aspnet/signalr';
import { Reading } from '../../../interfaces/resources/reading';
import { DataType } from '../../../enums/DataType';

@Component({
  selector: 'app-light-readings',
  templateUrl: './light-readings.component.html',
  styleUrls: ['./light-readings.component.css']
})
export class LightReadingsComponent implements OnInit {

  private hubConnection: HubConnection;
  public lightReadings: Array<Reading> = new Array();
  public movementReadings: Array<Reading> = new Array();

  constructor() { }

  ngOnInit() {
    console.log('Setting up the hub...');
    this.hubConnection = new HubConnectionBuilder()
      .withUrl(`${environment.general.api_hostname}/sensorReadings`)
      .build();

    this.hubConnection
      .start()
      .then(() => console.log('Connection started!'))
      .catch(err => console.log('Error while establishing connection'));

      this.hubConnection.on('sendSensorReadings', (readings: Reading[]) => {
        console.log(readings);

        const newLightReadings = readings.filter(r => r.dataType === DataType.Light);
        this.lightReadings = this.lightReadings.concat(newLightReadings);

        const newMovementReadings = readings.filter(r => r.dataType === DataType.Movement);
        this.movementReadings = this.movementReadings.concat(newMovementReadings);
      });
  }
}
