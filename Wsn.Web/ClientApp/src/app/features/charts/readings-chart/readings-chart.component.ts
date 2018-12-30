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
  public fromDate = this.getMonthBeginning();
  public toDate = this.getNow();

  constructor(private readonly api: ApiClientService) { }

  ngOnInit() {
    this.getDataAndUpdateChart(this.fromDate, this.toDate);
  }

  private getDataAndUpdateChart(from: Date, to: Date) {
    this.api.getReadings(from, to, this.dataType).subscribe(readings => {
      this.setChart(readings);
    });
  }

  private setChart(readings: Reading[]) {
    this.readings = readings;
    this.readings.forEach(r => r.date = new Date(r.date));
    this.chart = this.generateChart();
  }

  private generateChart(): Chart {
    return this.chart = new Chart(this.chartId, {
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

  public OnRefreshClick() {
    this.getDataAndUpdateChart(this.fromDate, this.toDate);
  }

  private getMonthBeginning(): Date {
    const now = new Date(Date.now());
    return new Date(now.getFullYear(), now.getMonth());
  }

  private getNow(): Date {
    return new Date(Date.now());
  }

}
