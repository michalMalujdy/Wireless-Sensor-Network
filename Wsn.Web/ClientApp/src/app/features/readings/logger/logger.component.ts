import { Component, OnInit, Input } from '@angular/core';
import { Reading } from '../../../interfaces/resources/reading';

@Component({
  selector: 'app-logger',
  templateUrl: './logger.component.html',
  styleUrls: ['./logger.component.css']
})
export class LoggerComponent implements OnInit {

  @Input() title: string;
  @Input() logs: Array<Reading>;
  @Input() maxWidth = 400;

  constructor() { }

  ngOnInit() {
  }

}
