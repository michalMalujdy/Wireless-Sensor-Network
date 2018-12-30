import { ApiClientService } from './../../../core/api-client.service';
import { Component, OnInit } from '@angular/core';
import { Reading } from '../../../interfaces/resources/reading';
import { DataType } from '../../../enums/DataType';

@Component({
  selector: 'app-charts',
  templateUrl: './charts.component.html',
  styleUrls: ['./charts.component.css']
})
export class ChartsComponent implements OnInit {

  public readings: Reading[];

  constructor(private readonly api: ApiClientService) { }

  ngOnInit() {
    this.api.getReadings(new Date(2000, 0), new Date(2020, 0), DataType.Light).subscribe(readings => {
        this.readings = readings;
      }
    );
  }

}
