import { Chart } from 'chart.js';
import { Component, OnInit, Input } from '@angular/core';
import { DataType } from '../../../enums/DataType';
import { Reading } from '../../../interfaces/resources/reading';
import { ApiClientService } from '../../../core/api-client.service';

@Component({
  selector: 'app-readings-chart',
  templateUrl: './readings-chart.component.html',
  styleUrls: ['./readings-chart.component.css']
})
export class ReadingsChartComponent implements OnInit {

  @Input() chartId: string;
  @Input() title: string;
  @Input() dataType: DataType;

  public readings: Reading[];
  public chart: any;
  public fromDate = this.getNow();
  public fromTime = '00:00';
  public toDate = this.getNow();
  public toTime = '12:00';

  constructor(private readonly api: ApiClientService) { }

  ngOnInit() {
    this.getDataAndUpdateChart(this.fromDate, this.toDate);
  }

  private getDataAndUpdateChart(from: Date, to: Date) {
    const fromDateTime = this.concatenateDateTime(from, this.fromTime);
    const toDateTime = this.concatenateDateTime(to, this.toTime);

    this.api.getReadings(fromDateTime, toDateTime, this.dataType).subscribe(readings => {
      this.setChart(readings.items);
    });
  }

  private setChart(readings: Reading[]) {
    this.readings = readings;
    this.readings.forEach(r => r.date = new Date(r.date));
    this.chart = this.generateChart();
  }

  private generateChart(): Chart {
    return this.chart = new Chart(this.chartId, {
      type: 'bar',
      data: {
        datasets: [{
          data: this.readings.map(r => r.value),
          backgroundColor: '#ebf3f9'
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

  public OnRefreshClick() {
    this.getDataAndUpdateChart(this.fromDate, this.toDate);
  }

  private getNow(): Date {
    return new Date(Date.now());
  }

  private concatenateDateTime(date: Date, time: string): Date {
    const hours = Number.parseInt(time.substring(0, time.indexOf(':')));
    const minutes = Number.parseInt(time.substring(time.indexOf(':') + 1));

    console.log(hours);
    console.log(minutes);

    return new Date(
      date.getFullYear(),
      date.getMonth(),
      date.getDate(),
      hours, minutes);
  }
}
