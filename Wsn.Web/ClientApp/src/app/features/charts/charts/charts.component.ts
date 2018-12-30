import { ApiClientService } from './../../../core/api-client.service';
import { Component, OnInit } from '@angular/core';
import { Reading } from '../../../interfaces/resources/reading';
import { DataType } from '../../../enums/DataType';
import { Chart } from 'chart.js';

@Component({
  selector: 'app-charts',
  templateUrl: './charts.component.html',
  styleUrls: ['./charts.component.css']
})
export class ChartsComponent implements OnInit {

  public readings: Reading[];
  public chart: any;

  constructor(private readonly api: ApiClientService) { }

  ngOnInit() {
    this.api.getReadings(new Date(2000, 0), new Date(2020, 0), DataType.Light).subscribe(readings => {
        this.readings = readings;
        this.readings.forEach(r => r.date = new Date(r.date));
        console.log(this.readings.map(r => r.date));

        this.chart = this.generateChart();
      }
    );
  }

  private generateChart(): Chart {
    return this.chart = new Chart('canvas', {
      type: 'line',
      data: {
        datasets: [{
          data: this.readings.map(r => r.value)
      }],
      labels: this.readings.map(r => this.getLabelDate(r.date)),
      },
      options: {
        responsive: true,
        maintainAspectRatio: false,
        legend: {
          display: false
        },
        scales: {
          xAxes: [{
            display: false
          }],
          yAxes: [{
            display: true
          }],
        }
      }
    });
  }
  private getLabelDate(date: Date): string {
    return date.toLocaleString();
  }

}
